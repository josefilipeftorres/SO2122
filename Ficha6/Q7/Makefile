.PHONY: clean client server1 servern

client:
	gcc -Wall tcp_client.c -o client
	./client localhost 5001

server1:
	gcc -Wall tcp_server_1.c -o server_1
	./server_1

servern:
	gcc -Wall tcp_server_n.c -o server_n
	./server_n
	fuser -k -n tcp 5001

clean:
	rm -rf client server_1 server_n *~

