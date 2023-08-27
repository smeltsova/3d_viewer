#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "./QtGifImage/gifimage/qgifimage.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "./core/affinity.h"
#include "./core/parser.h"

#ifdef __cplusplus
}
#endif

class MyOpenGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 private:
  float xRot = 0, yRot = 0, zRot = 0;
  float dx = 0, dy = 0, dz = 0;
  float xScale = 1, yScale = 1, zScale = 1;
  void initSettings();
  int vertex_size = 10;
  int edge_size = 1;
  int vertex_mode = 1;
  int edge_mode = 0;
  int projection_type = 0;
  void setupPerspective();
  void drawPoints();
  void drawLines();

 public:
  QColor backgroundColor = QColorConstants::Black;
  QColor edgeColor = QColorConstants::Green;
  QColor vertexColor = QColorConstants::Red;
  MyOpenGLWidget(QWidget *parent = nullptr);
  ~MyOpenGLWidget();
  obj_data obj = {0};
  int fileopen = 0;
  void setXTranslate(const QString &new_x);
  void setYTranslate(const QString &new_y);
  void setZTranslate(const QString &new_z);
  void setXRotate(const QString &new_x);
  void setYRotate(const QString &new_y);
  void setZRotate(const QString &new_z);
  void setXScale(const QString &new_x);
  void setYScale(const QString &new_y);
  void setZScale(const QString &new_z);

  void changePointSize(int size);
  void changeLineSize(int size);
  void changeVertexMode(int mode);
  void changeEdgeMode(int mode);
  void changeProjectionType(int type);

 protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
};

#endif  // MYOPENGLWIDGET_H
