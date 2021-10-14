# Automato_Celular_Blin
Projeto de um jogo de Vida, criado no 2º Semestre de Ciência da Computação da PUC SP
  
Nome e RA dos integrantes:  
Julio Cesar Barboza Filho RA: 00297586  
Lucas Costa Pessoa Graziano RA: 00297851  
Mateus Assatli Santana RA: 00301457  
Rafael Calado Moderno de Carvalho RA: 00279983  
Paloma Godoy Santos RA: 00184001  
  
- Introdução:  
    Em 1970, o cientista John Conway inventou um jogo que simula o processo de nascimento, sobrevivência e morte. O jogo da vida é um autômato celular e foi criado de modo a 
reproduzir, através de regras simples, as alterações e mudanças em grupos de seres vivos, tendo aplicações em diversas áreas da ciência. A ideia base é que um ser vivo necessita 
de outros seres vivos para sobreviver e procriar, mas um excesso de densidade populacional provoca a morte do ser vivo devido à escassez de comida. Os indivíduos vivem num mundo 
matricial e a geração seguinte é gerada a partir da geração anterior de acordo com as seguintes regras, A cada geração, as regras devem ser aplicadas para todos os seres vivos ao 
mesmo tempo, isto é, no mesmo passo para obter o próximo passo ou geração. :    
  
  - Reprodução: Um ser vivo nasce numa célula vazia se essa célula vazia tiver exatamente 3 seres vivos vizinhos. 
  - Sobrevivência: Um ser vivo que tenha 2 ou 3 vizinhos sobrevive para a geração seguinte. 
  - Morte por falta de comida: Um ser vivo com 4 ou mais vizinhos morre porque fica sem comida. 
  - Morte por solidão: Um ser vivo com 0 ou 1 vizinhos morre de solidão.
