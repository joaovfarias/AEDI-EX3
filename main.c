/*
Faça uma agenda capaz de incluir, apagar, buscar e listar
quantas pessoas o usuário desejar, porém, toda a informação
incluída na agenda deve ficar num único lugar chamado: “void
*pBuffer”.
Não pergunte para o usuário quantas pessoas ele vai incluir.
Não pode alocar espaço para mais pessoas do que o
necessário.
Cada pessoa tem nome[10], idade e telefone.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *AdicionarPessoa(void *p);
void ListarPessoas(void *p);
void BuscarPessoa(void *p);
char *RemoverPessoa(void *p);

int call = 1;

int main(){

    void *pBuffer = NULL;
    int esc;

    while (1){
        do{
            printf("\n");
            printf("1- Adicionar\n");
            printf("2- Remover\n");
            printf("3- Buscar\n");
            printf("4- Listar\n");
            printf("5- Sair\n");
            printf("Digite sua escolha: ");
            scanf("%d", & esc);
        }while (esc < 1 || esc > 5);
        switch (esc){
        case 1:
            pBuffer = AdicionarPessoa(pBuffer);
            break;
        case 2:
            pBuffer = RemoverPessoa(pBuffer);
            break;
        case 3:
            BuscarPessoa(pBuffer);
            break;
        case 4:
            ListarPessoas(pBuffer);
            break;
        case 5:
            return 0;
            break;
        }
    }

}

char *AdicionarPessoa(void *p){

    char nome[10];
    int idade;
    int telefone;

    printf("Nome: ");
    scanf("%s", nome);
    printf("Idade: ");
    scanf("%d", &idade);
    printf("Telefone: ");
    scanf("%d", &telefone);

    if (p == NULL){
        p = (char *)malloc(sizeof(nome) + sizeof(idade) + sizeof(telefone));
        strcpy(p, nome);
        p += sizeof(nome); 
        *(int *)p = idade;
        p += sizeof(int);
        *(int *)p = telefone;
        p -= sizeof(nome) + sizeof(int);
        call++;
        return p;
    }
    else{
        p = (char *)realloc(p, (sizeof(nome) + sizeof(idade) + sizeof(telefone)) * call);
        p += (sizeof(nome) + sizeof(idade) + sizeof(telefone)) * (call - 1);
        strcpy(p, nome);
        p += sizeof(nome);
        *(int *)p = idade;
        p += sizeof(int);
        *(int *)p = telefone;
        p -= (sizeof(nome) + sizeof(int));
        p -= (sizeof(nome) + sizeof(idade) + sizeof(telefone)) * (call - 1);
        call++;
        return p;
    }
}

void ListarPessoas(void *p){

    char nome[10];

    int pLength = (call - 1) * (sizeof(nome) + (sizeof(int) * 2));
    int contador = 0;

    while (contador != pLength){
        printf("\n");
        printf("Nome: %s\n", p);
        p += sizeof(nome);
        contador += sizeof(nome);
        printf("Idade: %d\n", *(int *)p);
        p += sizeof(int);
        contador += sizeof(int);
        printf("Telefone: %d\n", *(int *)p);
        p += sizeof(int);
        contador += sizeof(int);
    }

}

void BuscarPessoa(void *p){

    if (p == NULL){
        printf("Nao e possivel encontrar um nome\n");
        return;
    }
    
    char nome[10];
    int pLength = (call - 1) * (sizeof(nome) + (sizeof(int) * 2));
    int contador = 0;

    printf("Digite o nome: ");
    scanf("%s", nome);

    while (contador != pLength){
        if(strcmp(nome, p) == 0){
            printf("\n");
            printf("Nome: %s\n", p);
            p += sizeof(nome);
            printf("Idade: %d\n", *(int *)p);
            p += sizeof(int);
            printf("Telefone: %d\n", *(int *)p);
            return;
        }
        else{
            p += sizeof(nome) + (sizeof(int) * 2);
            contador += sizeof(nome) + (sizeof(int) * 2);
        }
    }
    printf("Nenhum nome foi encontrado\n");
    return;
}

char *RemoverPessoa(void *p){

    void *inicio = p;
    void *final = p;
    char nome[10];
    int pLength = (call - 1) * (sizeof(nome) + (sizeof(int) * 2));
    int contador = 0;

    printf("Nome: ");
    scanf("%s", nome);

    while (contador != pLength){
        if(strcmp(nome, p) == 0){
            final += sizeof(nome) + (sizeof(int) * 2);
            memmove(p, final, pLength - (contador + (sizeof(nome) + (sizeof(int) * 2))));
            p = inicio;
            p = (char *)realloc(p, (pLength - (sizeof(nome) + (sizeof(int) * 2))));
            call--;
            return p;
        }
        else{
            p += sizeof(nome) + (sizeof(int) * 2);
            contador += sizeof(nome) + (sizeof(int) * 2);
            final = p;
        }
    }
    printf("Nome nao encontrado\n");
    p = inicio;
    return p;
}