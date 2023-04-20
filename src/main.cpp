// main.cpp

#include "utility.hpp"
#include "network.hpp"

int main(int argc, char **argv) {
	network net;
	ip_address myIp = ip_address(192, 168, 0, 103, 55596);
	struct message {
		int acknowledgeNr;
		int sequenceNr;
		float deltaTimeFromRecieved;
	};
	float timeRecieved;
	float deltaFromRecieved;
	ip_address clientIp = ip_address::k_any_host;
	byte_stream stream;
	message msg = {};
	udp_socket m_socket;
	m_socket.open(myIp);
	int m_acknowledgeNr = 0;
	int m_sequenceNr = 0;
	bool networkRunning = true;
	while (networkRunning) {
		
		if (m_socket.receive(clientIp, stream)) {
			timeRecieved = timespan::time_since_start().elapsed_seconds();
			byte_stream_reader reader(stream);
			while (reader.has_data()) {
				msg.acknowledgeNr = m_acknowledgeNr;
				msg.sequenceNr = reader.serialize(msg.sequenceNr);
			}
			byte_stream_writer writer(stream);
			writer.serialize(msg.sequenceNr);
			writer.serialize(msg.acknowledgeNr);
			deltaFromRecieved = timespan::time_since_start().elapsed_seconds() - timeRecieved;
			writer.serialize(msg.deltaTimeFromRecieved = deltaFromRecieved);
			if (m_socket.send(clientIp, stream)) {
				m_acknowledgeNr++;
			}

		}
	}
	

	
	
	

	return 0;
}
