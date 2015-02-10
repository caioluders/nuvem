# nuvem
Exemplos de algoritmos para um carrinho seguidor de linha com Arduino , com apenas um sensor de preto/branco.

* A biblioteca "Ultrasonic" é necessária para o funcionamento dos códigos*

## Algoritmo de Parkinson

O carrinho começa no branco e procura a linha preta , girando para o lado , se acha-la , procura o branco , e assim por diante.

###Pseudo-Código

```
vire(direção) :
	se direção == esquerda :
		pare(roda esquerda)
		gire(roda direita)
	se direção == direita :
		pare(roda direita)
		gire(roda esquerda)

loop :
	estado = ler_sensor()
	se estado == true :      // true == branco ; false == preto
		vire(direita)
	senão :
		vire(esquerda)
```

###Representação visual

```
		   C┃
		   ╱┃
		   ╲┃
		   ╱┃
		   ╲┃
		   ╱┃
		   ╲┃
		   ╱┃

┃ --> Linha preta
╱ ou ╲ --> Caminho percorrido pelo carrinho
C --> Carrinho
```

*P.s: Parkinson porque o carrinho fica se tremendo Hu3*

##Minhoca

A ideia aqui é fazer um algoritmo mais preciso e rápido. Ele sempre procura a parte branca , passando pela linha preta. Com um contador sabemos para que lado o carro deve seguir.

###Pseudo-código

```
cont = 0

vire(direção) :
	se direção == esquerda :
		pare(roda esquerda)
		gire(roda direita)
	se direção == direita :
		pare(roda direita)
		gire(roda esquerda)

ande() :
	se ( cont % 2 ) == 0 :
		vire(esquerda)
	senão :	
		vire(direita)

loop :
	estado = ler_sensor()

	se estado == true :
		cont++
		ande()
```

###Representação visual

```
		  C ┃
		   ╲┃
		    ┃╲
		    ┃╱
		   ╱┃
		   ╲┃
		    ┃╲	
		    ┃╱
		    ┃

┃ --> Linha preta
╱ ou ╲ --> Caminho percorrido pelo carrinho
C --> Carrinho
```

*P.s:O percuso parece o de uma minhoca.*
*P.s 2:As curvas não são acentuadas como na representação , são bastantes brandas.*

*Nota : Este algoritmo não se mostrou tão preciso , mas mais eficiente , fazendo grandes curvas antes de voltar a tocar a linha.*
