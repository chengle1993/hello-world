/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#include <qpid/messaging/Connection.h>
#include <qpid/messaging/Message.h>
#include <qpid/messaging/Receiver.h>
#include <qpid/messaging/Session.h>

#include <cstdlib>
#include <iostream>

#include <sstream>

using namespace qpid::messaging;
using namespace qpid::types;

using std::stringstream;
using std::string;

int main(int argc, char** argv) {
    const char* url = argc>1 ? argv[1] : "amqp:tcp:121.36.223.246:5672";
    const char* address = argc>2 ? argv[2] : "message_queue; {create: always, mode: consume}";
	//const char* address = argc>2 ? argv[2] : "message_topic; {create: always, node:{type:topic, durable:true} }";
	//const char* address = argc>2 ? argv[2] : "message_fanout; {create: always, node:{type:topic, durable:true, x-declare:{type:fanout}} }";
	std::string connectionOptions = argc > 3 ? argv[3] : "{reconnect: true, reconnect_timeout: 10}";

    Connection connection(url, connectionOptions);
    try {
        connection.open();
		while (true)
		{
			Session session = connection.createSession();
			Receiver receiver = session.createReceiver(address);
			std::cout << receiver.fetch().getContentObject() << std::endl;
			session.acknowledge();
			receiver.close();
		}
        
        connection.close();
        return 0;
    } catch(const std::exception& error) {
        std::cout << error.what() << std::endl;
        connection.close();
    }
    return 1;
}
