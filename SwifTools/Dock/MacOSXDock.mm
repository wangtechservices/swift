#include "SwifTools/Dock/MacOSXDock.h"

#include <AppKit/AppKit.h>
#include <Cocoa/Cocoa.h>
#include <boost/lexical_cast.hpp>

#include "Swiften/Base/String.h"

namespace Swift {

MacOSXDock::MacOSXDock(CocoaApplication*) {
}

void MacOSXDock::setNumberOfPendingMessages(int i) {
	String label(i > 0 ? boost::lexical_cast<std::string>(i) : "");
	NSString *labelString = [[NSString alloc] initWithUTF8String: label.getUTF8Data()];
	[[NSApp dockTile] setBadgeLabel: labelString];
	[labelString release];
	[NSApp requestUserAttention: NSInformationalRequest];
}

}
