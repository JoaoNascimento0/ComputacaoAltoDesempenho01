em uma primeira implementacao quis fazer apenas o basico.

definir um primeiro esboço do projeto.

O coeficiente de difusao nao precisa ser uma constante, fica mais facil de fazer se for. Ele pode ser dependente tanto de u, x, y, e t, isto é, dependencia em relacao a concentracao, as posições e também dependencia temporal.


Para a proxima versao:
    -   Implementar uma funcao que recebe uma matriz, implementa as condições de contorno, fazer isso pode ajudar a deixar o codigo mais limpo [];
    -   Definir um metodo para solucao do sistema linear, o prof falou gradiente conjugado, mas se fizer por Decomposicao LU, depois podemos usar método de crout [];
    -   Implementar a funcao DiferencasFInitas [];
    -   Aprender a usar a diretiva #define para funcoes [];

Perguntas: 
    -   Até que ponto é ruim para agilidade do código criar e destruir muitos arrays?
    -   É melhor criar um novo array calloc ou limpar um array antigo?
    -   Um D, nao constante, ou nao linear poderia se uma boa para diferenciar o projeto?