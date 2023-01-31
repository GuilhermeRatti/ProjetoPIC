Link para o github do projeto no unity: https://github.com/MatheusLSG/ProjetoPIC

Resumo:
  Nosso projeto consiste na criação de uma Luva VR para captar as rotações no espaço tridimensional 
  e replicá-lo em um ambiente virtual no “Unity”, a fim de criar um simples jogo para equilibrar uma 
  bola em uma superfície pelo maior tempo possível com a adição de alguns obstáculos. 


Descrição:

  O projeto se define em uma integração físico-virtual de uma interação de um
objeto acoplado na mão da pessoa, que seria uma luva, possuindo o circuito
montado nele, contendo o arduino, o sensor de giro e aceleração, um receptor de
pressão binário(botão ou sensor de pressão diferente). Junto a isso, utiliza-se o
software “unity”, do qual se irá fazer um algoritmo que permitirá aquela interação da
mão humana com o virtual, ou seja, conforme movimentos que a pessoa realizará
com a mão, isso será expressado em tempo real no software, em uma animação 3d
de realidade virtual. Será possível a pessoa fazer movimentos de giro com a mão,
em sentidos e ângulos diferentes, por exemplo.

Detalhe:
    1 - Nem todas as informações captadas pelo giroscópio são mandadas com êxito para o Unity.
Portanto, movimento muito brusco e pouco intervalado com as mãos, não será garantido a reprodução do movimento da mão
no mini jogo do unity.
