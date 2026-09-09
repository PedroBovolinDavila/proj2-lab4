# Documentação do Sistema de Calibração

Esta documentação descreve o funcionamento do código em C responsável por ler, calibrar e calcular estatísticas de um conjunto de até 10 sensores. O sistema permite a entrada manual de dados de sensores, realiza correções de medidas com base em ganho e offset, e apresenta a média antes e depois da calibração, bem como o sensor com a maior medida aferida.

## Estruturas de Dados e Constantes

```c
#define MAX_SENSORES 10
```
Define o limite máximo de sensores que o programa pode processar simultaneamente.

### `struct Sensor`
Estrutura utilizada para armazenar os dados de cada sensor individualmente. Contém os seguintes campos:
* **`canal`** (int): O canal do sensor (0 ou 1).
* **`ganho`** (double): O ganho aplicado na calibração (deve estar entre 10V e 10.4V).
* **`offset`** (double): O valor de compensação (entre -1 e 1).
* **`medida`** (double): A medida atual registrada pelo sensor (bruta ou calibrada).

## Funções

### `void calibrar_sensor(struct Sensor* sensor)`
**Descrição:** Calibra a medida de um sensor específico.

A função utiliza a fórmula matemática:  
`medida_corrigida = (ganho * medida) + offset`  
para atualizar o valor da medida diretamente no endereço de memória do sensor passado.

**Parâmetros:**
* `sensor` (`struct Sensor*`) - Ponteiro para o sensor que terá a medida calibrada.

**Retorno:** `void` (Nenhum valor retornado, alteração feita por referência).

---

### `void mostrar_sensor(const struct Sensor sensor, int numero_sensor)`
**Descrição:** Mostra os detalhes de um sensor no console.

A função recebe uma cópia de um sensor e o seu número de identificação, exibindo suas propriedades (canal, ganho, offset e medida) em uma formatação padronizada e legível.

**Parâmetros:**
* `sensor` (`const struct Sensor`) - Estrutura do sensor que será mostrada na tela.
* `numero_sensor` (`int`) - Número de identificação/ordem do sensor para exibição.

**Retorno:** `void` (Imprime os dados no console).

---

### `double calcular_media(const struct Sensor* sensores, int qtd_sensores)`
**Descrição:** Calcula a média aritmética das medidas dos sensores.

A função percorre o vetor de sensores fornecido, acumulando a soma de todas as medidas em uma variável temporária. Ao final, divide essa soma pela quantidade de sensores para obter a média.

**Parâmetros:**
* `sensores` (`const struct Sensor*`) - Vetor contendo os sensores avaliados.
* `qtd_sensores` (`int`) - Quantidade de elementos válidos no vetor de sensores.

**Retorno:** `double` - O valor numérico correspondente à média aritmética das medidas.

---

### `int indice_maior(const struct Sensor* sensores, int qtd_sensores)`
**Descrição:** Retorna o índice do sensor com a maior medida registrada.

A função percorre o vetor de sensores e compara sequencialmente as medidas. Armazena o índice do sensor que possui o maior valor de medida encontrado durante o loop.

**Parâmetros:**
* `sensores` (`const struct Sensor*`) - Vetor contendo os sensores que serão avaliados.
* `qtd_sensores` (`int`) - Quantidade de elementos válidos no vetor de sensores.

**Retorno:** `int` - O índice numérico (base 0) do elemento no vetor que possui a maior medida.
