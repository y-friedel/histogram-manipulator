#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../src/Image.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void load_img();
    void apply_filter();
    
private:
    Ui::MainWindow *ui;
    Image img;
    Image output;
};

#endif // MAINWINDOW_H
