# Zombie Game - Marcelo Vitor - 221030034

Um jogo 2D desenvolvido em C++ com foco em componentes de engine, incluindo sistema de câmera, animadores, mapas de tiles (tile maps) e mecânicas essenciais como detecção de colisão (hit detection) e fundos em paralaxe (parallax backgrounds).

Este projeto foi desenvolvido como parte das entregas do **Trabalho 4**.

## Estrutura do Projeto

- `bin/` - Contém os arquivos objetos compilado dos jogo, como o arquivo `Game.o`.
- `Recursos/` - Diretório dedicado aos arquivos de mídia e assets do jogo, incluindo os arquivos de áudio (ex: `BGM.wav`).
- `Makefile` - Script de automação de compilação.
- `.gitignore` - Arquivos e diretórios ignorados pelo Git.

## Como Executar

O projeto possui um `Makefile` configurado na raiz para facilitar o processo de compilação e execução.

1. Abra o terminal na pasta raiz do projeto.
2. Compile o código executando o comando:
   ```bash
   make
   ```
3. Após a compilação, execute o jogo gerado com o comando:
   ```bash
   ./JOGO
   ```

## Funcionalidades Implementadas

- **Hit Detection:** Sistema de detecção de colisão preciso para as interações.
- **Parallax Background:** Fundo dinâmico com múltiplas camadas para criar a ilusão de profundidade e movimento.
- **Camera System:** Câmera 2D otimizada para acompanhar a ação.
- **Animators & Tile Maps:** Gerenciamento da renderização de texturas, mapas e animações dos personagens.

## Tecnologias e Ferramentas

- C++
- Make
