# TP3
TP3 taller de programacion 1

* Alumno: Alasino Franco
* Padron: 102165
* URL: https://github.com/alasinofranco3/TP2

## Descripcion de la resolucion del trabajo:
Para la realizacion de este trabajo me plantee comenzar primero con la funcionalidad y logica del juego para un unico cliente ,llegar al correcto funcionamiento y una vez resuelto eso proceder a extenderlo a un servidor multicliente.

Lo primero que hice fue pasar la implementacion del Socket que tenia hecha en C a C++,tarea que no fue muy complicada gracias a los videos de las clases, en los cuales se explicaba lo fundamental para realizar esto.

Luego, continue con la implementacion del parser del archivo de numeros del servidor,que tampoco fue demasiado complicado ya que era algo que ya veniamos haciendo en TPs anteriores.

Luego comence a trabajar en la logica del juego,la clase mas importante de este proceso es la clase Protocol que tiene los metodos necesarios para procesar,validar,enviar y recibir los comandos y numeros que requiere el juego.Este clase es utilizada tanto por el cliente como por el servidor.

Finalmente, una vez que la logica del juego estaba implementada para un solo cliente,prosegui a extenderlo a multiples clientes, usando las clases AcceptorSocket y PeerClient,que heredan de Thread, logre correr tanto el socket aceptador del servidor como sus multiples peer sockets o peer clients en hilos diferentes.Siguiendo los consejos dados en clase acerca del servidor multicliente esta tarea resulto no ser tan complicada como esperaba.El servidor funciona de la siguiente manera : un hilo principal lanza el hilo aceptador y espera por un caracter para cerrar el servidor, luego el hilo aceptador va aceptando varios clientes y corriendolos en nuevos hilos en los cuales se desarrolla la partida de cada cliente.Una vez que se recibe comando de cierre del servidor, el socket aceptador se cierra, y este espera a que todos los clientes terminen sus respectivas partidas.Finalmente el servidor imprime los resultados de todas las partidas.

Una vez que el socket aceptador se cierra, el accept falla por lo que debo catchear la excepcion lanzada por el Socket accept.En este caso como la variable del socket aceptador finished esta en true (ya se cerro el servidor) ,esta excepcion no representa un problema por lo que la ejecucion del programa continua exitosamente.En caso contrario,si el accept falla y el socket aceptador no termino si representa un error y relanzamos la excepcion.

La dificultad mas grande que tuve en este trabajo fue la utilizacion de move semantics y del std::move,por ejemplo cuando debia pasar le socket devuelto por el accept a algun constructor de la clase PeerClient.Al principio no lograba moverlo con exito por lo tanto, el socket que se guardaba en el cliente no era el mismo devuelto por el accept del socket aceptador.Esto me generaba obvios problemas de comunicacion entre el servidor y el cliente.Este problema me llevo bastante tiempo resolverlo y entender mejor como es que el std::move funciona,pero finalmente logre utilzarlo correctamente.

## Diagramas:

![diagrama_threads_tp3](https://user-images.githubusercontent.com/50004705/82866659-be03f180-9eff-11ea-802c-c9870a70bfbd.png)

* Diagrama que muestra los componentes y relaciones de las clases PeerClient y AcceptorSocket

![diagrama_server_client_tp3](https://user-images.githubusercontent.com/50004705/82866664-bf351e80-9eff-11ea-852c-6a496b99f6d9.png)

* Diagrama que muestra los componentes y relaciones de las clases Server y Client

## Aclaraciones:

* El polimorfismo lo aplique en la clase Thread en el metodo run, ya que tanto el PeerClient como el AcceptorSocket sobreescriben ese metodo
con el comportamiento correspondiente.

* La sobrecarga del operador () la realice en el ProtectedCounter, esta sobrecarga me permite utilizar dicho operador para sumarle al contador el valor pasado por parametro.

* En la clase AcceptorSocket sobrecargue el operador = para que me permita hacer copias de las referencias a los contadores y al vector de respuestas del objeto pasado por parametro.
