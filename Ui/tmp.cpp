#include "temp.h"
#include <QtWidgets/QApplication>

Login::Login()
{
	setWindowIcon(QIcon("C:/Users/Zahra/Desktop/web38.png"));
	setWindowTitle("Login Form");
	user_name_label->setText("Username");
	password_label->setText("Password");
	password_lineedit->setEchoMode(QLineEdit::Password);
	user_name->addItem("Administrator");
	database->setIcon(QIcon("C:/Users/Zahra/Desktop/server13.png"));
	database->setIconSize(QSize(40, 40));
	connect(database, SIGNAL(clicked()), this, SLOT(messagebox()));
	// left layout
	left_layout0->addWidget(user_name_label);
	left_layout0->addWidget(password_label);
	left_layout1->addWidget(user_name);
	left_layout1->addWidget(password_lineedit);
	left_layout->addLayout(left_layout0, 0, 0);
	left_layout->addLayout(left_layout1, 0, 1);
	// right layout
	right_layout->addWidget(database);
	// main layout
	main->addLayout(right_layout);
	main->addLayout(left_layout);
	setLayout(main);
}

void Login::messagebox()
{
	QMessageBox *message = new QMessageBox(this);
	message->setText("Message");
	message->setInformativeText("CLicked SIGNA has been Emited ! ");
	message->setStandardButtons(QMessageBox::Ok);
	message->show();
}
