![LogiKidsLogo](https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/logo.png)

## Introdução
**LogiKids** é um jogo educativo para auxiliar crianças no desenvolvimento lógico. Utiliza diversos problemas comuns da Computação de maneira lúdica para estimular o raciocínio e familiarizar o público infantil com problemas lógicos. 

## Puzzles

### O problema das N-Rainhas 
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/nqueens.png" width="400">

### Coloração de Mapas
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/mapcoloring.png" width="400">

### A Torre de Hanói
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/hanoi.png" width="400">

### O Problema da Mochila
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/knapsack.png" width="400">

### Os Pesos da Balança
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/scale.png" width="400">

### O problema do Caixeiro Viajante
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/tsp.png" width="400">

## Outras Features

### Seleção de Nível
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/levels.png" width="400">

### Dicas
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/tip.png" width="400">

### Pontuação
<img src="https://github.com/ketlynsena/LogiKids/blob/main/LogiKids/sample_images/win.png" width="400">

## Grupo
- Ketlyn Caroline Sena de Castro
- Scarlet Gianasi Viana

## Escopo Funcional
- Modo história com pequenos puzzles
- Botão ajuda com tutorial
- Botão sair da aplicação
-	Pontuação do usuário
-	Interação com objetos na tela
-	Dicas
-	Seleção de nível

## Tecnologias
- Linguagem: `C++`
- Framework: `SDL2`

## SPRINT 1

**Histórias e Tarefas:**
- Menu principal
  - Inicializar o Jogo - Scarlet
  - Renderizador de Texturas - Scarlet 
  - Gerenciador de Texturas - Scarlet 
- Menu de Seleção de Nível
  - Mudança de Seleção de Estados do Jogo - Ketlyn
  - Criação de Objetos do Jogo - Ketlyn
  - Reposicionamento e Movimento de objeto do Jogo - Ketlyn
  - Gerenciador de Eventos - Ketlyn
- Modo História
  - Renderização de Texto - Scarlet
  - Mockups das Telas do Jogo - Scarlet
  - Geração de Assets - Scarlet

### Retrospectiva:
- **O que deu certo na Sprint 1?**
  Foi possível implementar o framework básico para a criação dos próximos componentes do jogo. A divisão de tarefas foi feita com muito diálogo entre os membros da equipe, o que permitiu um desenvolvimento síncrono. O primeiro sprint também teve como objetivo pensar primeiramente no design tanto do jogo como das interfaces, e, com isso, será possível avançar mais na implementação propriamente dita nos próximos sprints.
  
- **O que deu errado na Sprint 1?**
 Foi necessário mudar a ferramenta escolhida inicialmente (Godot) porque não permitia o cálculo da cobertura de testes, o que atrasou o desenvolvimento das tarefas. Com isso, não foi possível implementar os testes de unidade.
 Nos próximos sprints esses problemas iniciais já foram resolvidos, então a equipe espera atingir todos os objetivos e realizar mais testes de unidade.
 
 ## SPRINT 2
 
 **Histórias e Tarefas:**
- Puzzle N-Rainhas
  - Lógica N-Rainhas -Scarlet
  - Assets Puzzle N-Rainhas - Scarlet
  - Classe de Nível N-Rainhas - Scarlet
  - Testes Unitarios N-Rainhas - Ketlyn
  - Teste Unitarios da Classe GameObject -Ketlyn
- Puzzle Coloração de Mapas
  - Lógica Coloração de Mapas - Ketlyn
  - Assets Puzzle Coloração de Mapas - Scarlet
  - Classe de Nível Coloração de Mapas - Scarlet
  - Testes Unitarios Coloração de Mapas - Ketlyn
- Puzzle Torre de Hanoi
  - Lógica Torre de Hanoi - Ketlyn
  - Assets Puzzle Torre de Hanoi - Scarlet
  - Classe de Nível Torre de Hanoi - Scarlet
  - Testes Unitarios Torre de Hanoi - Ketlyn
 

### Retrospectiva:
- **O que deu certo na Sprint 2?**
  Nessa sprint foi possivel terminar a implementação de três puzzles, N-Rainhas, coloração de mapas e da torre de Hanoi, como estava previsto. Além disso a interfase grafica do jogo foi refinada e agora apresenta a versão final das telas implementadas. Também criamos o projeto de para testes e implementamos testes unitarios para algumas classes do jogo.
  
- **O que deu errado na Sprint 2?**
  Não conseguimos fazer testes para todas as classes dentro da sprint e alcançar a cobertura de testes desejada.
