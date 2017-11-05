#ifndef CLICK_ROUTINGELEMENT_HH
#define CLICK_ROUTINGELEMENT_HH
#include <click/element.hh>
CLICK_DECLS

/*
 *	Click element that will:
 *	- function like a routing element for the agent
 *	- handle incoming messages like the ICMP solicitations message
 *	- handle the registration request message at the agent side
 *	- generate specific replies depending the current situation
 *	Input 0 ==> messages with DST 255.255.255.255
 *	Input 1 ==> directed messages to the agent itself
 * 	Output 0 ==> packets to private network
 *	Output 1 ==> packets to agent itself
*/
class RoutingElement : public Element {
	public:
		RoutingElement();
		~RoutingElement();

		const char *class_name() const	{ return "RoutingElement"; }
		const char *port_count() const	{ return "2/2"; }
		const char *processing() const	{ return PUSH; }
		int configure(Vector<String>&, ErrorHandler*);
		void push(int, Packet* p);

	private:
		// IPAddress of the agent
		IPAddress _agentAddressPublic;
};

CLICK_ENDDECLS
#endif
