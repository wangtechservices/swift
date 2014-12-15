/*
 * Copyright (c) 2010 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <map>

#include <QObject>
#include <SwifTools/Notifier/Notifier.h>
#include <SwifTools/Notifier/SnarlNotifier.h>

class QSystemTrayIcon;

namespace Swift {
	class WindowsNotifier : public QObject, public Notifier {
			Q_OBJECT

		public:
			WindowsNotifier(const std::string& name, const boost::filesystem::path& icon, QSystemTrayIcon* tray);
			~WindowsNotifier();

			virtual void showMessage(Type type, const std::string& subject, const std::string& description, const boost::filesystem::path& picture, boost::function<void()> callback);
			virtual void purgeCallbacks();

		private slots:
			void handleMessageClicked();

		private:
			QSystemTrayIcon* tray;
			Win32NotifierWindow* notifierWindow;
			SnarlNotifier* snarlNotifier;
			boost::function<void()> lastCallback;
	};
}
