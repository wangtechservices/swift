/*
 * Copyright (c) 2015 Daniel Baczynski
 * Licensed under the Simplified BSD license.
 * See Documentation/Licenses/BSD-simplified.txt for more information.
 */

/*
 * Copyright (c) 2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#include <Swift/QtUI/QtEmoticonCell.h>

namespace Swift {

QtEmoticonCell::QtEmoticonCell(const QString emoticonAsText, QString filePath, QWidget* parent) :  QLabel(parent), emoticonAsText_(emoticonAsText) {
	if (filePath.startsWith("qrc:/")) {
		filePath.remove(0, 3);
	}
	setPixmap(QPixmap(filePath));
	setToolTip(emoticonAsText_);
}

QtEmoticonCell::~QtEmoticonCell() {

}

void QtEmoticonCell::mousePressEvent (QMouseEvent* event) {
	emit emoticonClicked(emoticonAsText_);
	QLabel::mousePressEvent(event);
}

}


