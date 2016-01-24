#ifndef TEMP_H
#define TEMP_H
#include <QtWidgets>

class Login : public QDialog {
private:
	QLabel *user_name_label = new QLabel;
	QLabel *password_label = new QLabel;
	QLineEdit *password_lineedit = new QLineEdit;
	QComboBox *user_name = new QComboBox;
	QPushButton *database = new QPushButton("Setting");
	QVBoxLayout *left_layout0 = new QVBoxLayout;
	QVBoxLayout *left_layout1 = new QVBoxLayout;
	QGridLayout * left_layout = new QGridLayout;
	QVBoxLayout *right_layout = new QVBoxLayout;
	QHBoxLayout *main = new QHBoxLayout;
public:
	Login();
public slots:
	void messagebox();
};

#endif // TEMP_H
