#ifndef CLICK_ROUTINGELEMENT_HH
#define CLICK_ROUTINGELEMENT_HH
#include <click/element.hh>

// Local imports
#include "Advertiser.hh"

CLICK_DECLS
/*
 *	Click element that will:
 *	- function like a routing element for the agent
 *	- handle incoming messages like the ICMP solicitations message
 *	- handle the registration request message at the agent side
 *	- generate specific replies depending the current situation
 *	Input 0 ==> directed messages to the agent itself
 * 	Input 1 ==> messages from the CN
 * 	Output 0 ==> packets to private network
 *	Output 1 ==> packets to the public network
 * 	Output 2 ==> packets to the agent itself
*/
class RoutingElement : public Element {
	public:
		RoutingElement();
		~RoutingElement();

		const char *class_name() const	{ return "RoutingElement"; }
		const char *port_count() const	{ return "2/3"; }
		const char *processing() const	{ return PUSH; }
		int configure(Vector<String>&, ErrorHandler*);
		void push(int, Packet* p);

	private:
		// IPAddress of the agent
		IPAddress _agentAddressPublic;

		// Encapsulate the incoming IP packet in an outer IP header according RFC2003
		void _encapIPinIP(Packet* p);

		// Reference to the advertiser element
		Advertiser* _advertiser;

		// Creates an ip header with a different src and dst address
		click_ip* _createIp(const click_ip* iph, IPAddress newSrc, IPAddress newDest);
};

CLICK_ENDDECLS
#endif
