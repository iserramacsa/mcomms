#ifndef PRINTER_VIEW_H
#define PRINTER_VIEW_H

#include <QWidget>
#include <QtGui>
#include "ui_printerview.h"

class PrinterView : public QWidget
{
		Q_OBJECT
	public:
		explicit PrinterView(QWidget* parent = 0);
		~PrinterView();

	private:
		Ui::PrinterView ui;
};


#endif //PRINTER_VIEW_H
