# Sistema de Arquivos EXT4 Shell

Este projeto é uma implementação de um shell para manipulação de imagens de sistema de arquivos EXT4. O shell oferece um conjunto de operações que permitem visualizar informações, navegar pelo sistema de arquivos e executar ações específicas em arquivos e diretórios.

## Requisitos

- Compilador GCC
- Sistema operacional Linux (o projeto é específico para sistemas de arquivos EXT4)

## Compilação

Para compilar o projeto, execute o comando `make` no terminal:

```bash
make
```

## Uso

Execute o programa a partir do terminal, fornecendo o caminho para a imagem do sistema de arquivos EXT4 como argumento:

```bash
./bin/ext4shell minha_imagem.img
```

## Operações Suportadas

1. **info:** Exibir informações da imagem e do sistema de arquivos.
2. **cat `<file>`:** Exibir o conteúdo de um arquivo no formato texto.
3. **attr `<file | dir>`:** Exibir os atributos de um arquivo ou diretório.
4. **cd `<path>`:** Alterar o diretório corrente para o definido como path.
5. **ls:** Listar arquivos e diretórios no diretório corrente.
6. **testi `<inode_number>`:** Verificar se um inode está livre ou ocupado.
7. **testb `<block_number>`:** Verificar se um bloco está livre ou ocupado.
8. **export `<source_path>` `<target_path>`:** Copiar arquivo da imagem para o sistema operacional da máquina.
9. **pwd:** Exibir o diretório corrente (caminho absoluto).
10. **touch `<file>`:** Criar o arquivo com conteúdo vazio.
11. **mkdir `<dir>`:** Criar o diretório vazio.
12. **rm `<file>`:** Remover o arquivo do sistema.
13. **rmdir `<dir>`:** Remover o diretório, se estiver vazio.
14. **rename `<file>` `<newfilename>`:** Renomear arquivo para um novo nome.


