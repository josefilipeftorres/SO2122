# Sistemas de Operação

## Q1

- Um número complexo z ∈ C. Z tem a forma `x + yi`, onde x,y ∈ R. Os valores x e y representam, respetivamente, as partes real e imaginária de z.

- `complex.h` define um novo tipo (complex) que pode ser usado para implementar uma biblioteca de funções que realizam as operações sobre complexos de forma simplificada. Junto da definição do novo tipo, também possui a lista completa dos ti+os destas funções (`API`).

- `use_complex.c` faz uso da API definida para criar e manipular números complexos.

- `complex.c` contém a implementação da API.

- Execução:
    1. Compilamos primeiro a API e construimos uma biblioteca **libcomplex.a** que será usada pelo programa principal:
        - `$ gcc -Wall -c complex.c`
        - `$ ar -rc libcomplex.a complex.o`
        - `$ ar -t libcomplex.a`
    2. Compilamos depois o programa principal **use_complex.c** indicando ao compilador **(linker)** que deve usar a biblioteca **libcomplex.a** `(-lcomplex)` situada no diretório corrente `(-L.)`:
        - `$ gcc -Wall -o use_complex use_complex.c -L. -lcomplex -lm`

        *Nota: também incluimos a biblioteca `math.h`, por isso temos que a ligar ao programa `-lm`*

## Q2

- Repetição do exercício anterior mas criando uma biblioteca dinâmica

- `$ gcc -c -Wall -fPIC -o complex.o complex.c`
- `$ gcc -shared -o libcomplex.so complex.o`
    - *-fPIC* indica ao compilador que deve gerar código binário que possa ser colocado em qualquer posição na memória
    - *-shared* indica ao compilador que a biblioteca resultante vai ser um *shared object*, com extensão **.so**
    - Depois criada a biblioteca, está é usada da mesma forma que uma biblioteca estática
- `$ gcc -Wall -o use_complex use_complex.c -L. -lcomplex -lm`
- `$ ./use_complex`

    *Nota: Se não der, use o seguinte comando, `$ export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH` para a biblioteca ser encontrada.*

## Q3 & Q4 & Q5

- Fazer a implementação da API

## Q6

- Criar um novo tipo num cabeçalho (ficheiro.h) e definir os métodos da API