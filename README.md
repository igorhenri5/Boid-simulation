# Boid-simulation
TP2-CG

  Cada boid é uma entidade independente, que possui uma posição no espaço e um vetor
velocidade associado. O movimento do bando obedece um conjunto básico de elementos:

• Separação: cada boid deve manter uma certa distância mínima de separação entre
ele mesmo e os boids vizinhos (ou outros obstáculos que podem estar presentes
no cenário).

• Coesão: Os boids devem se manter unidos no bando. Na presença de obstáculos,
eles até podem se separar para evitar o obstáculo, mas devem se reagrupar uma
vez vencido o obstáculo (assumindo que esse não seja muito grande).

• Alinhamento: Os boids tendem a se mover na mesma direção e com a mesma
velocidade que os boids vizinhos.

O conjunto de restrições acima definem a natureza do movimento num nível local, mas
não define o movimento coletivo do grupo. 

Para tanto, o programa deverá implementar um boid especial que representa o objetivo, ou seja, o grupo, como um tudo, tende a voar
na direção desse boid-objetivo. Tanto os boids quanto o boid-objetivo devem ser inicializados com valores razoáveis, e o vetor velocidade do boid-objetivo deve ser
controlado pelo usuário através de comandos do teclado (ou do mouse). Lembre-se de ajustar a direção e o módulo do vetor velocidade de cada boid, de forma a manter o grupo.

#### Esse trabalho deve ter como funcionalidade básica, valendo 80% da nota, os seguintes itens:

1) Deve haver um mundo razoavelmente grande definido, com um “chão” que pode
ser modelado por um plano horizontal. No centro desse mundo deve haver uma
torre em forma de cone.

2) Devem haver pelo menos 3 modos de visualização distinos: o primeiro com o olho
posicionado no alto da torre no centro do mundo, o segudo atrás do bando, à uma
distância fixa, e o terceiro perpendicular ao vetor que representa a velocidade do
bando, e paralelo ao plano do chão. Em todos os três modos, a direção de
visualização é partindo do olho para o centro do bando (ponto médio das posições
de cada boid) com a normal apontando perpendicular ao plano do chão.

3) O mundo deve ser iluminado, podendo usar o modelo global padrão do OpenGL.

4) Cada boid deve ser desenhado como um poliedro tridimensional.

5) O número de boids deve poder variar de acordo com comandos do
usuário, por exemplo, pressionando a tecla “+” deve criar um novo
boid aleatoriamente (perto do bando) e a tecla “-” elimina um boid aleatoriamente
do bando.

6) Os boids devem ter movimentos animados correspondente ao batido das asas.
Isso pode ser implementado acrescentando um estado a cada boid, que
corresponde à posição da asa. Cada boid tem o seu estado independente dos
demais.

#### O restante da nota do trabalho pode ser obtida implementando as funcionalidades extras sugeridas abaixo:
1) Obstáculos (10%): além do chão e da torre de visualização, outros objetos podem
ser acrescentados à cena (sugestões sendo esferas e cones, cujos algoritmos de
inteseção com raios estão dadas nas notas da disciplina) e os boids deve evitar
colisões com esses obstáculos inclusive violando os outros fatores determinantes
do comportamento do grupo. O boid-objetivo é um fantasma, e passa através de
obstáculos.

2) Sombras (5%): Não é necessário projetar sombra de um boid no outro, mas apenas
uma projeção paralela simples dos boids no chão. Modelos mais sofisticados
podem ter mais pontos extras

3) Fog (5%): funcionalidade acrescentada por comando do teclado, podendo ser
habilitada e desabilitada durante a execução

4) Modo de pausa (5%): acionado pelo teclado para a simulação dos bois congelando
a imagem (bois podem ser acrescentados e retirados durante a pausa). Acrescente
também o modo de depuração. Incluindo o modo de execução passo-a-passo com
impressão para depuração.

5) Reshape (5%): permitir o redimensionamento da janela de visualização.

6) Banking (10%): um objeto no espaço está sujeito a rotações em 3 eixos básicos.
Assumindo a base ortonormal onde X aponta para frente (em relação ao objeto),
Z para cima (em relação ao mundo) e Y é o produto vetorial de X e Z (para o lado),
a rotação em torno de Y é chamada pitch, e faz o objeto apontar pra cima quando
sobe e pra baixo quando desce. A rotação em torno de Z se chama yaw, e
basicamente faz o objeto apontar pra direção (lateral) em que voa. A rotação em
X, se chama row, e o ato de executar essa rotação se chama banking. O ângulo de
row está relacionado com a taxa da curva (derivada segunda da trajetória). O
cálculo de um ângulo de row suave pode ser complicado, portanto preste atenção.
