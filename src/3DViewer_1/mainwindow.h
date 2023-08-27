#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "./QtGifImage/gifimage/qgifimage.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "./core/affinity.h"
#include "./core/parser.h"

#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void resetPosition();
  void initColors();
  void on_pushButton_file_clicked();
  void connectSetup();

  void on_horizontalScrollBar_rotate_x_valueChanged(int value);

  void on_horizontalScrollBar_rotate_y_valueChanged(int value);

  void on_horizontalScrollBar_rotate_z_valueChanged(int value);

  void on_horizontalScrollBar_translate_x_valueChanged(int value);

  void on_horizontalScrollBar_translate_y_valueChanged(int value);

  void on_horizontalScrollBar_translate_z_valueChanged(int value);

  void on_horizontalScrollBar_scale_x_valueChanged(int value);

  void on_horizontalScrollBar_scale_y_valueChanged(int value);

  void on_horizontalScrollBar_scale_z_valueChanged(int value);

  void on_doubleSpinBox_translate_x_valueChanged(double arg1);

  void on_doubleSpinBox_translate_y_valueChanged(double arg1);

  void on_doubleSpinBox_translate_z_valueChanged(double arg1);

  void on_doubleSpinBox_rotate_x_valueChanged(double arg1);

  void on_doubleSpinBox_rotate_y_valueChanged(double arg1);

  void on_doubleSpinBox_rotate_z_valueChanged(double arg1);

  void on_doubleSpinBox_scale_x_valueChanged(double arg1);

  void on_doubleSpinBox_scale_y_valueChanged(double arg1);

  void on_doubleSpinBox_scale_z_valueChanged(double arg1);

  void on_radioButton_none_pressed();

  void on_radioButton_square_pressed();

  void on_radioButton_circle_pressed();

  void on_radioButton_solid_pressed();

  void on_radioButton_dashed_pressed();

  void on_radioButton_parallel_pressed();

  void on_radioButton_central_pressed();

  void on_pushButton_change_color_vertices_clicked();

  void on_pushButton_change_color_edges_clicked();

  void on_pushButton_change_color_edges_2_clicked();

  void on_pushButton_reset_clicked();

  void loadSettings();

  void setSettings();

  void on_pushButton_screenshot_clicked();

  void on_pushButton_gif_clicked();

  void slotTimer();

 private:
  Ui::MainWindow *ui;
  QString settingFile;
  QTimer *timer;
  QGifImage *gif;
  QImage *image;
  int frame_count = 0;
};
#endif  // MAINWINDOW_H
