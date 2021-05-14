# Buscador de Conteúdo em C
Projeto desenvolvido para a matéria de Métodos de Pesquisa e Ordenação em Estruturas de Dados da PUCPR.

# Sobre o projeto
A partir de palavras-chave, o sistema retorna uma lista de arquivos ordenada por um critério de relevância e utiliza as estruturas de dados especificadas (Listas e Árvores). 
A busca é feita sobre arquivos com extensão .txt armazenados em um diretório específico.
Durante as fases do projeto, foi preciso implementar e adaptar os seguintes elementos: 
- Representação e busca em uma lista encadeada;
- Representação e busca em árvore binária de busca;
- Algoritmo de ordenação para ranqueamento.

# Funcionamento
 1. Solicita a entrada dos termos e armazena-os em uma struct; 
 2. Faz a leitura dos arquivos contando a frequência que o termo aparece em cada arquivo.
 3. Armazena o em uma lista o nome do arquivo e a frequencia do termo; 
 3. Armazena em uma Árvore o termo e a lista; 
 4. Busca na Árvore os termos armazenados somando as frequencias dos arquivos de mesmo nome inserindo-os em uma nova lista; 
 5. Realiza a ordenação da lista;
 6. Mostra na tela a lista ordenada;
 
## Tela
![Modelo Conceitual](https://github.com/mayconlyn/assets/blob/master/Desafios/Estrutura%20de%20dados/Tela.png)

# Tecnologias utilizadas
- Linguagem C
- Code Blocks

# Autor

Maycon Lyncoln Garcia

https://www.linkedin.com/in/maycon-garcia-66a820112/

