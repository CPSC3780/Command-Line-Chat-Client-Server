#pragma once

// STL
#include <vector>
#include <cstdint>

// Boost
#include <boost/asio.hpp>
#include <boost/thread.hpp>

// Project
#include "../Common/dataMessage.h"

class client
{
	enum Protocol
	{
		p_UNDEFINED = 0,
		p_UDP = 1,
		p_BLUETOOTH = 2
	};

public:

	//-------------------------------------------------------------- constructor
	// Brief Description
	//  Constructor for the client
	//
	// Method:    client
	// FullName:  client::client
	// Access:    public 
	// Returns:   
	// Parameter: const std::string& username
	// Parameter: const uint16_t& inServerPort
	// Parameter: const int8_t& inServerIndex
	// Parameter: boost::asio::io_service& ioService
	//--------------------------------------------------------------------------
	client(
		const std::string& username,
		const uint16_t& inServerPort,
		const int8_t& inServerIndex,
		boost::asio::io_service &ioService);

	//---------------------------------------------------------------------- run
	// Brief Description
	//  Creates a thread for each major function of the client. These functions
	//  loop indefinitely.
	//
	// Method:    run
	// FullName:  client::run
	// Access:    public 
	// Returns:   void
	//--------------------------------------------------------------------------
	void run();

private:
	
	//------------------------------------------------------------------ getLoop
	// Brief Description
	//  The client loop that periodically sends get requests to the server.
	//  Essentially, this is what drives the client. Without it, the client
	//  would never receive any messages.
	//
	// Method:    getLoop
	// FullName:  client::getLoop
	// Access:    private 
	// Returns:   void
	//--------------------------------------------------------------------------
	void getLoop();

	//---------------------------------------------------------------- inputLoop
	// Brief Description
	//  Input loop for getting input from the user via command line. The input
	//  is parsed and converted to a data message, which is sent to the server
	//  the client has established a connection with.
	//
	// Method:    inputLoop
	// FullName:  client::inputLoop
	// Access:    private 
	// Returns:   void
	//--------------------------------------------------------------------------
	void inputLoop();

	//-------------------------------------------------------------- sendOverUDP
	// Brief Description
	//  Sends messages to the server over UDP.
	//
	// Method:    sendOverUDP
	// FullName:  client::sendOverUDP
	// Access:    private 
	// Returns:   void
	// Parameter: const dataMessage& message
	//--------------------------------------------------------------------------
	void sendOverUDP(
		const dataMessage& message);
	
	//-------------------------------------------------------- sendOverBluetooth
	// Brief Description
	//  Relays messages to the server over Bluetooth.
	//
	// Method:    sendOverBluetooth
	// FullName:  client::sendOverBluetooth
	// Access:    private 
	// Returns:   void
	// Parameter: const dataMessage & message
	//--------------------------------------------------------------------------
	void sendOverBluetooth(
		const dataMessage& message);

	//-------------------------------------------------------------- receiveLoop
	// Brief Description
	//  The client's receive loop, it receives the messages from the server 
	//  over the supported protocols.
	//
	// Method:    receiveLoop
	// FullName:  client::receiveLoop
	// Access:    private 
	// Returns:   void
	//--------------------------------------------------------------------------
	void receiveLoop();

	//----------------------------------------------------------- receiveOverUDP
	// Brief Description
	//  Receives messages from the server over UDP.
	//
	// Method:    receiveOverUDP
	// FullName:  client::receiveOverUDP
	// Access:    private 
	// Returns:   void
	//--------------------------------------------------------------------------
	void receiveOverUDP();

	//----------------------------------------------------- receiveOverBluetooth
	// Brief Description
	//  Receives messages from the server over Bluetooth.
	//
	// Method:    receiveOverBluetooth
	// FullName:  client::receiveOverBluetooth
	// Access:    private 
	// Returns:   void
	//--------------------------------------------------------------------------
	void receiveOverBluetooth();

	//----------------------------------------------------------- sequenceNumber
	// Brief Description
	//  The sequence number for the client. This increments every time it is
	//  called and can be used to verify which messages were received by
	//  the server.
	//
	// Method:    sequenceNumber
	// FullName:  client::sequenceNumber
	// Access:    private 
	// Returns:   const int64_t&
	//--------------------------------------------------------------------------
	const int64_t& sequenceNumber();

	// Member Variables
	boost::asio::ip::udp::socket m_UDPsocket;
	boost::asio::ip::udp::resolver m_resolver;
	boost::asio::ip::udp::endpoint m_serverEndPoint;
	boost::thread_group m_threads;
	client::Protocol m_activeProtocol;
	bool m_terminate;
	int64_t m_sequenceNumber;
	std::string m_username;
	uint16_t m_serverPort;
	int8_t m_serverIndex;
};