# Minishell - Testes e Erros a Tratar

## 📌 Introdução
Este documento tem como objetivo organizar e documentar os testes e correções implementadas no projeto Minishell. Atualmente, as funcionalidades pendentes incluem a implementação do pipe, algumas validações e a correção de vazamentos de memória.

## 🔍 Testes a serem realizados
Os testes devem ser comparados com o comportamento do bash padrão. Para cada teste, utilize o **valgrind** para verificar possíveis vazamentos de memória. Recomenda-se testar cada funcionalidade individualmente para identificar com precisão a origem de possíveis leaks.

### 🛠️ Compilação
- Verificar o **Makefile**:
  - Compilador utilizado.
  - Flags de compilação.
  - Relink e targets obrigatórios.
  
### 🖥️ Comandos Simples e Variáveis Globais
- Executar comandos sem argumentos:
  ```sh
  /bin/ls
  /bin/clear
  ```
- Testar comando vazio (`""` ou `''`) e comparar com o bash.
- Testar linha com apenas espaços ou tabs e verificar se são armazenados no histórico.

### 📜 Argumentos
- Executar comandos com caminho absoluto e argumentos:
  ```sh
  /bin/ls -l
  ```

### 🗣️ Echo
Comparar todas as saídas com o bash:
```sh
echo
echo ''
echo ""
echo 'echo'
echo "echo"
echo -n
echo -nnnn felix
echo eymar'felix'"eymar"luanda
echo $USER
echo '$USER'
echo "\$USER"
echo $
echo $@ $@@ $@@@@
```

### 🚪 Exit
Testar diferentes valores de saída e verificar o `echo $?`:
```sh
exit
exit ""
exit -1
exit 0
exit 1
exit 9223372036854775807
exit a
echo $?
```

### 🔄 Status de Retorno de Processos
Após cada comando, verificar o exit status com `echo $?`.

### 🚦 Sinais
- Testar `Ctrl-C`, `Ctrl-D` e verificar o `echo $?` (deve ser `130`).

### 📝 Aspas Duplas e Simples
Verificar se pipes e redirecionamentos dentro de aspas são tratados como argumentos:
```sh
echo "cat lol.c | cat > lol.c"
echo '>' aaa
echo '$USER'
```

### 🌍 Variáveis de Ambiente
```sh
env
env 42
export
echo $USER
export a='test'
unset a
```

### 📂 Comando CD
```sh
cd
cd ..
cd .
cd pasta_existente
cd pasta_inexistente
```

### 📌 PWD
```sh
pwd
pwd sss
```

### 📁 Caminhos Relativos e PATH
Testar comandos comuns como `ls`, `touch`, `wc`.

### ➡️ Redirecionamento
Testar redirecionamentos simples e duplos:
```sh
echo edson >
< file_existente
<<
echo edson > a baptista > b finda > c
```

### | Pipes
- Verificar syntax errors, pipe no início e no fim da linha.

### 🔀 Casos Especiais
Testar cenários inesperados e comandos sequenciais:
```sh
cat | cat | ls
echo $USER$USER
```

## 🚀 Alterações e Melhorias Implementadas
✅ Implementação de comandos básicos.
✅ Suporte a variáveis de ambiente.
✅ Expansão de variáveis (`$USER`, `$@`, `$?`).
✅ Suporte a aspas simples e duplas.
✅ Tratamento de `Ctrl-C` e `Ctrl-D`.
✅ Melhorias na estrutura de dados.
✅ Correção de alguns vazamentos de memória.

## ❗ Próximos Passos
🔲 Implementar pipes (`|`).
🔲 Melhorar validações de entrada.
🔲 Corrigir vazamentos de memória.

---
Este documento será atualizado conforme o progresso do projeto. Continue testando e comparando com o bash para garantir um comportamento fiel ao original!