
# How does internet works?

//put an image

# Why do we use Socket.io/Websocket instead of HTTP?

- HTTP request is made when you establish a connection once -> assign IP/port -> send request -> get response from server -> connection closed
- To communicate again you need to establish a connection
- Its better to use sockets in these cases as they keep the port open for incoming and outgoing msgs

// put an image of working of sockets

# Difference between WebSockets and Socket.io?

// uplload image
- WebSockets is the build in browser socket accessed through JS
- Any native server or database cant communicate over websockets, hence, we need to provide a translator between them. Socket.io does that job here
