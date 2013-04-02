import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.EOFException;
import java.io.IOException;
import java.net.Socket;
import java.net.SocketException;
import java.util.ArrayList;
import java.util.Iterator;

public class ClientStub {
	public static byte[] readMessage(DataInputStream in) {
		byte[] message = null;
		// There's no way in java to know if the socket closed on the other side
		// We can only read something and see if it throws a java.io.EOFException
		try {
			byte size = in.readByte();
			message = new byte[size];
			in.readFully(message);
		} catch (EOFException e) {
			return null;
		} catch (IOException e) {
			e.printStackTrace();
			return null;
		}
		return message;
	}
	
	public static void sendMessage(final byte[] message, DataOutputStream out) {
		byte size = (byte) message.length;
		try {
			out.writeByte(size);
			out.write(message);
		} catch (SocketException e) {
			return;
		} catch (IOException e) {
			e.printStackTrace();
			return;
		}
	}
	
	public static void main(String args[]) {
		if (args.length < 4) {
			System.out.println("Usage: ./client server_hostname server_port opponent_level(1=dumb, 5, 7, 8) own_level(1=dumb, 5, 7, 8)");
			return;
		}
		// variabile pentru conexiune
		Socket socket = null;
		DataOutputStream out = null;
        DataInputStream in = null;
        Tabla tabla = new Tabla();
        
		try {
			// realizez conexiunea la server
			socket = new Socket(args[0], Integer.parseInt(args[1]));
			// scriu in out pe socket
			out = new DataOutputStream(socket.getOutputStream());
			// citesc din in de pe socket
            in = new DataInputStream(socket.getInputStream());
            
            // trimit primul mesaj - dificulatea adversarului
            byte[] message = new byte[1];
            message[0] = Byte.parseByte(args[2]);
            Connection.sendMessage(message, out);
            
            // primesc raspuns cu culoarea mea
            message = Connection.readMessage(in);
            if (message[0] == 1) {
            	System.out.println("Jucatorul Negru");
            } else if (message[0] == 0) {
            	System.out.println("Jucatorul Alb");
            } else {
            	System.err.println("Eroare");
            }
            int turn = 0;
            int player = message[0];
            int opponent = player==0? 1 : 0;
            
            while (true) {
            	message = Connection.readMessage(in);
            	// Primesti un mesaj de la server care contine miscarile adversarului si zarul tau 
            	// Daca sunteti primii la mutare, atunci nu primiti mutari din partea adversarului
            	// Daca adversarul nu a putut sa mute, atunci nu primiti mutari din partea adversarului
            	System.out.println("Mesajul primit :");
            	for(int i=0; i<message.length;i++){
            		
            		System.out.print(message[i]+" ");
            	}
            	Zar zar = new Zar(0, 0);
            	Integer[] mutariadversar = new Integer[message.length];
            	if(message[0]!= 87 && message[0] != 76){
            		
	            	if(player == 0 && turn==0){
	            		
	            		zar = new Zar(message[0], message[1]);
	            		
	            	}
	            	
	            	else{
	            		
	            		 for(int i = 0; i< message.length-2;i++){
	            			 mutariadversar[i] = (int) message[i];
	            		 }
	            		 
	            		 zar = new Zar(message[message.length-2], message[message.length-1]);
	            		 
	            	}
	            	
	            	
	            	int i = 0;
	            	// parcurgem mutarile adversarului si facem schimbarile 
	            	while(mutariadversar[i]!=null){
		            	if(mutariadversar[i] == 30){
		            		if(opponent == 0){
		            			mutariadversar[i] = 25;
		            		}else{
		            			mutariadversar[i] = 0;
		            		}
		            	}
		            	
	            		if(!tabla.move(mutariadversar[i], mutariadversar[i+1], opponent)){
	            			System.err.println("SI MAI NASPA");
	            		}
	            		
	            		System.out.println(mutariadversar[i] + ","  + mutariadversar[i+1]);
	            		System.out.println("Tabla dupa mutarea adversar*********************** ");
	            		System.out.println(tabla);
	            		i+=2;
	            	}
	            	
	            	
	            	
	            	
            	} else{
            	// la un moment dat jocul se va termina
            		
	            	boolean gameOver = true;
	            	if (gameOver){
	            		System.out.println("GameOver");
	            		break;
	            	}
	            	
            	}
            	
            	turn ++;
            	// Compune mesajul tau; dimensiunea lui depinde de ceea ce vei trimite
            	//int len = zar.length()*2;
            	
            	
            	int i = 0;
            	// daca avem piese scoase de pe tabla au prioritate si le bagam iar cu mutarile ramase 
            	// alegem cea mai buna mutare 
            	System.out.println("\nzarul:");
            	System.out.println(zar);
            	ArrayList<Pair<Integer, Integer>> moves = new ArrayList<Pair<Integer, Integer>>();
            	
            	moves = tabla.best(tabla, zar, player);
            	
            	byte[] response;
            	
            	if(moves == null){
            		
            		response = new byte[1];
            		
            	}else {
            		System.out.println("Lungimea mesajului este " + moves.size());
            		response = new byte[moves.size()*2];
	            	
	            	System.out.println(moves.size());
	            	Iterator<Pair<Integer, Integer>> it = moves.iterator();
	            	System.out.println("Numarul de mutari");
	            	System.out.println(moves.size());
	            	while(it.hasNext()){
	            		
	            		Pair<Integer, Integer> p = it.next();
	            		if(p.getFirst()!=25 && p.getFirst() != 0){
		            		response[i] = Byte.parseByte(p.getFirst().toString());
		            		response[i+1] =Byte.parseByte(p.getSecond().toString());
	            		}else{
	            			int x = 30;
	            			response[i] = Byte.parseByte(String.valueOf(x));
		            		response[i+1] =Byte.parseByte(p.getSecond().toString());
	            		}
	            		System.out.println("Mutarea mea :");
	            		System.out.println(p);
	            		System.out.println(tabla);
	            		if(!tabla.move(p.getFirst(), p.getSecond(), player)){
	            			System.err.println("NASPA RAU");
	            		}
	            		i+=2;
	            	}
            	}
            	System.out.println("tabla dupa mutarea mea ====================");
            	System.out.println(tabla);
            	
            	Connection.sendMessage(response, out);
            	
            }
            socket.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println(e.getMessage());
		}
	}
}
