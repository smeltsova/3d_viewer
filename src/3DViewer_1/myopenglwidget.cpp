#include "myopenglwidget.h"

MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

MyOpenGLWidget::~MyOpenGLWidget() { free_obj_data(&obj); }

void MyOpenGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
}

void MyOpenGLWidget::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), backgroundColor.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setupPerspective();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  if (fileopen) {
    glVertexPointer(3, GL_FLOAT, 0, obj.vertex_array);
    glEnableClientState(GL_VERTEX_ARRAY);
    drawPoints();
    drawLines();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void MyOpenGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type == 0) {
    glOrtho(-1, 1, -1, 1, 1, 3);
  } else if (projection_type == 1) {
    glFrustum(-1, 1, -1, 1, 1, 3);
  }
}

void MyOpenGLWidget::setupPerspective() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection_type == 0) {
    glOrtho(-obj.max_coord, obj.max_coord, -obj.max_coord, obj.max_coord,
            -2 * obj.max_coord, obj.max_coord * 5);
  } else if (projection_type == 1) {
    GLdouble zNear = 0.01;
    GLdouble zFar = obj.max_coord * 10;
    GLdouble fovY = 60;
    GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
    GLdouble fW = fH;
    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
    glTranslatef(0, 0, -2.5 * obj.max_coord);
  }
}

void MyOpenGLWidget::drawPoints() {
  if (vertex_mode != 0) {
    if (vertex_mode == 1) glEnable(GL_POINT_SMOOTH);
    glPointSize(vertex_size);
    glColor3d(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
    glDrawArrays(GL_POINTS, 0, obj.vertex_number);
    if (vertex_mode == 1) glDisable(GL_POINT_SMOOTH);
  }
}
void MyOpenGLWidget::drawLines() {
  if (edge_mode == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00F0);
  }
  glColor3d(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());
  glLineWidth(edge_size);
  glDrawElements(GL_LINES, 2 * obj.edges_number, GL_UNSIGNED_INT,
                 obj.edges_array);
  if (edge_mode == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void MyOpenGLWidget::setXTranslate(const QString &new_x) {
  float new_dx = new_x.toFloat();
  translation(&obj, new_dx - dx, 0, 0);
  dx = new_dx;
  update();
}

void MyOpenGLWidget::setYTranslate(const QString &new_y) {
  float new_dy = new_y.toFloat();
  translation(&obj, 0, new_dy - dy, 0);
  dy = new_dy;
  update();
}

void MyOpenGLWidget::setZTranslate(const QString &new_z) {
  float new_dz = new_z.toFloat();
  translation(&obj, 0, 0, new_dz - dz);
  dz = new_dz;
  update();
}

void MyOpenGLWidget::setXRotate(const QString &deg) {
  float new_deg = deg.toFloat();
  rotation(&obj, new_deg - xRot, 'x');
  xRot = new_deg;
  update();
}

void MyOpenGLWidget::setYRotate(const QString &deg) {
  float new_deg = deg.toFloat();
  rotation(&obj, new_deg - yRot, 'y');
  yRot = new_deg;
  update();
}

void MyOpenGLWidget::setZRotate(const QString &deg) {
  float new_deg = deg.toFloat();
  rotation(&obj, new_deg - zRot, 'z');
  zRot = new_deg;
  update();
}

void MyOpenGLWidget::setXScale(const QString &scale) {
  float new_scale = scale.toFloat();
  if (new_scale != 0) {
    scaling(&obj, new_scale / xScale, 1, 1);
    xScale = new_scale;
    update();
  }
}

void MyOpenGLWidget::setYScale(const QString &scale) {
  float new_scale = scale.toFloat();
  if (new_scale != 0) {
    scaling(&obj, 1, new_scale / yScale, 1);
    yScale = new_scale;
    update();
  }
}

void MyOpenGLWidget::setZScale(const QString &scale) {
  float new_scale = scale.toFloat();
  if (new_scale != 0) {
    scaling(&obj, 1, 1, new_scale / zScale);
    zScale = new_scale;
    update();
  }
}

void MyOpenGLWidget::changePointSize(int size) {
  vertex_size = size;
  update();
}

void MyOpenGLWidget::changeLineSize(int size) {
  edge_size = size;
  update();
}

void MyOpenGLWidget::changeVertexMode(int mode) {
  vertex_mode = mode;
  update();
}

void MyOpenGLWidget::changeEdgeMode(int mode) {
  edge_mode = mode;
  update();
}

void MyOpenGLWidget::changeProjectionType(int type) {
  projection_type = type;
  update();
}
