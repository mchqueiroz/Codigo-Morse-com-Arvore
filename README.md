## Código Morse com Árvore ##

## DESCRIÇÃO : Programa baseado em árvore binária de busca que armazena, pesquisa e traduz código morse para símbolos alfanuméricos, e vice-versa.

## PRÉ-REQUISITOS:
		- Compilador de código C;
		- Arquivo txt na mesma pasta que o código do programa, caso o usuário deseje tradução de textos por txt;
		- Comandos por terminal;

## FUNCIONALIDADES : 
		- Traduzir texto alfanumérico em morse;
		- Traduzir texto em morse para mensagem alfanumérica;
		- Mostrar árvore binária alfanumérica / morse em pré ordem;
## USO :
	O programa inicializa printando uma árvore binária completa de nós alfanuméricos e caminhos de traço-ponto (esquerda é ".", direita é "-"). Cada caminho representa um código morse, enquanto o nó à letra correspondente. Por exemplo, percorrer esquerda esquerda esquerda esquerda, isso é, "....", corresponde ao nó de chave tipo char "H".
	- As letras DEVEM ESTAR EM MAÍUSCULO.
	- Cada sequência em código morse para uma letra correspondente DEVE ESTAR SEPARADA POR " " (espaço).
	- Caso deseje espaço (" ") entre palavras quando traduzindo de morse, UTILIZE "/".
	- NÃO É POSSÍVEL traduzir morse E codificar alfanúmericos NA MESMA MENSAGEM.

	Para usar a função de traduzir, é possível escolher por onde deseja que a leitura da mensagem a ser traduzida seja feita. Digite:
	
	1 : Caso deseja escrever uma mensagem alfanumérica OU em código morse pelo console.

	2 : Caso deseja que a mensagem alfanumerica OU em código morse seja lida de um arquivo .txt. 
	Depois de inicializar o programa, digite o nome do arquivo que deseja traduzir, incluindo a extensão.

	O resultado da tradução / codificação aparecerá no console (stdout).

## EXEMPLOS :
	
	Quando inserido "HELLO WORLD", o programa imprime "Resultado da traducao de "HELLO WORLD": .... . .-.. .-.. ---  / .-- --- .-. .-.. -..".
	Quando inserido "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG'S BACK 1234567890", o programa imprime "Resultado da Traducao de "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG'S BACK 1234567890": - .... .  / --.- ..- .. -.-. -.-  / -... .-. --- .-- -.  / ..-. --- -..-  / .--- ..- -- .--. . -..  / --- ...- . .-.  / - .... .  / .-.. .- --.. -.--  / -.. --- --.  ...  / -... .- -.-. -.-  / .---- ..--- ...-- ....- ..... -.... --... ---.. ----. ----- "
	O resultado é o mesmo quando enviado por STDIN ou FILE.

## INTEGRANTES :
	Leonardo Rodrigues Batista - RA: 845971
	Beatriz de Oliveira Franca - RA: 847155
	Vitor Matheus Oliveira Usar - RA: 845250
	Michael Queiroz Cardoso - RA: 845062
