/*
 * Copyright (c) 2010-2016 Isode Limited.
 * All rights reserved.
 * See the COPYING file for more information.
 */

#pragma once

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/optional/optional_fwd.hpp>
#include <boost/shared_ptr.hpp>

#include <Swiften/Base/API.h>
#include <Swiften/Base/boost_bsignals.h>
#include <Swiften/EventLoop/EventOwner.h>
#include <Swiften/Network/BoostConnection.h>
#include <Swiften/Network/ConnectionServer.h>

namespace Swift {
	class SWIFTEN_API BoostConnectionServer : public ConnectionServer, public EventOwner, public boost::enable_shared_from_this<BoostConnectionServer> {
		public:
			typedef boost::shared_ptr<BoostConnectionServer> ref;

			static ref create(int port, boost::shared_ptr<boost::asio::io_service> ioService, EventLoop* eventLoop) {
				return ref(new BoostConnectionServer(port, ioService, eventLoop));
			}

			static ref create(const HostAddress &address, int port, boost::shared_ptr<boost::asio::io_service> ioService, EventLoop* eventLoop) {
				return ref(new BoostConnectionServer(address, port, ioService, eventLoop));
			}

			virtual boost::optional<Error> tryStart(); // FIXME: This should become the new start
			virtual void start();
			virtual void stop();

			virtual HostAddressPort getAddressPort() const;

			boost::signal<void (boost::optional<Error>)> onStopped;

		private:
			BoostConnectionServer(int port, boost::shared_ptr<boost::asio::io_service> ioService, EventLoop* eventLoop);
			BoostConnectionServer(const HostAddress &address, int port, boost::shared_ptr<boost::asio::io_service> ioService, EventLoop* eventLoop);

			void stop(boost::optional<Error> e);
			void acceptNextConnection();
			void handleAccept(boost::shared_ptr<BoostConnection> newConnection, const boost::system::error_code& error);

		private:
			HostAddress address_;
			int port_;
			boost::shared_ptr<boost::asio::io_service> ioService_;
			EventLoop* eventLoop;
			boost::asio::ip::tcp::acceptor* acceptor_;
	};
}
