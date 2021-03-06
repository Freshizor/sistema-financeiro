/*Deyvidy Lu� Nascimento dos Santos*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
       
#define TAMC 5 //Tamanho do vetor da struct Cliente
#define TAMD 5 //Tamanho do vetor da struct Data
#define TAMH 5 //Tamanho do vetor da struct Historico
#define TAMM 5 //Tamanho do vetor da struct Movimentaca
#define QTDMAXDIA 2 // Tamanho das opercaoes diarias 
       
typedef struct CONTA {
    int codigo;
    char descricao[100];
    int status;
}Client;
            
typedef struct HISTORICO {
    int codigo;
    char descricao[100];
    char tipoDeTransacao;
    int status;
}Historico;
          
typedef struct DATA{
    int dia, mes, ano;
}Data;
          
typedef struct MOVIMENTACAO{
    Data data;
    Client client;
    Historico historico;
    float valor;
    char complemento[100];
    int status;
    int cod;
}Movimentacao;
   
//Declaraco das structs 
Client client [TAMC];
  
Historico historico [TAMH];
  
Data data [TAMD];
  
Movimentacao movimentacao [TAMM];   
  
//Declara??o das fun?oes      
void menu ( );
void menuExibir ( );
void menuExcluir ( );
void menuAlterar ( );
  
void cadastraConta ( int codigo, int i );
void excluirContaCliente ( );
void alterarConta ( );
  
void cadastraHistorico ( int codigo, int j );
void historicoExpecifico( );
void excluirHistorico( );
void alterarHistorico ( );
  
void realizarOperacoes ( );
void exibirOperacao ( int i );
int verificarData( int dia, int mes, int ano );
void alterarOperacao ( );
void exibirPorDatas ( );

void listarMovimentacoes ( );
void listarTodasOpercaoes ( );
void excluirOperacao( ); 
void login ( );
Client dadosClient ( int conta );
  
float processarOpercao ( );
void exibirContaEspecifica ( );
void consultarContaCliente ( );
void exibirHistorico ( int j );
void consultarHistorico( );
int buscaHistorico ( int codigo );
void exibir ( int pos );
  
int verificarPosicaoHistorico ( );
int verificarCodHistorico ( int codigo );
  
int verificarPosicao ( );
int verificarCod ( int codigo );
     
// variaveis globais (contador) para saber o tamanho do vetor  (opercao) par saber quantas operacoes foram feitas;  
int contador = 0, operacao = 0, his = 0, statusConta=0, movi=0;
  
//===============================MENU========================================    
int main ( ) {
    system("cls");
    int op, posicao, posicaoH, verificaCodigo, confirmacao, confirmacaoH, conta;
    char opcoes;
      
     printf("\t===============================\n"); 
     printf("\tSISTEMA DE CONTROLE FINANCEIRO\n");
     printf("\t===============================\n\n");
      
    do { 
        printf("[1]\t Cadastra conta\n[2]\t Cadastra historico\n[3]\t Entra na conta\n");
        printf("[0]\t Sair\n\n");
        printf("Escolha uma opcao acima: ");
        scanf("%s",&opcoes);
           
    switch ( opcoes ) {
        case '1' : {
        	system("cls");
            posicao = verificarPosicao ( );
            if( posicao != -1 ) {
                    
                printf("Codigo da Conta: \n");
                scanf("%d",&verificaCodigo);
                    
                confirmacao = verificarCod( verificaCodigo);
                    
                if( confirmacao == 1 )
                    cadastraConta( verificaCodigo, posicao );
                else
                    printf("\nCodigo ja existente\n");
            }
            else
                printf("\nNao e possivel realizar mais cadastros!\n");         
            break;
        }
        case '2' : {
            posicaoH = verificarPosicaoHistorico ( );
            if( posicaoH != -1 ) {
                    
                printf("Codigo do Historico: \n");
                scanf("%d",&verificaCodigo);
                    
                confirmacaoH = verificarCodHistorico( verificaCodigo);
                    
                if( confirmacaoH == 1 )
                    cadastraHistorico ( verificaCodigo, posicaoH );
                else
                    printf("\nCodigo do historico ja existente\n");
            }
            else
                printf("\nNao e possivel realizar mais cadastros!\n");     
            break;
            }
        case '3' :
            login ( );              
            break;
        case '0' :
            printf("Bye!!\n"); 
            break;          
        default :
            printf("opcao invalida\n");
            break;
        }
        }while( opcoes !='0' ); 
         
    system("pause");
    system("cls");
}
     
void menu ( ) {
    system("cls");
      
    int op, posicao, posicaoH, verificaCodigo, confirmacao, confirmacaoH, conta;
    char opcoes;
    
	printf("\t===============================\n"); 
	printf("\tSISTEMA DE CONTROLE FINANCEIRO\n");
	printf("\t===============================\n\n");
      
    do { 
    if( statusConta != 0 ) {
        printf("\t\t\t\%s\n",dadosClient(statusConta).descricao);
    }
    printf("[1]\t Realizar operacao\n[2]\t Exibir operacoes feitas nesta conta\n[3]\t Saldo\n");
    printf("[4]\t Exibir\n");
    printf("[5]\t Alterar\n");
    printf("[6]\t Excluir\n");
    printf("[0]\t Voltar\n\n");
    printf("Escolha uma opcao acima: ");
    scanf("%s",&opcoes);
       
    switch ( opcoes ) {
    case '1' : {
        realizarOperacoes  ( );       
        break;
    }
    case '2' : {
        listarMovimentacoes ( );    
        break;
    }
    case '3' :
        processarOpercao ( );
        break; 
	case '4' :
        menuExibir ( );
        break;
    case '5' :
        menuAlterar ( );              
        break;
    case '6' :
        menuExcluir ( );      
        break;	 
    case '0' :
        statusConta=0;
        main( );
        break;          
    default :
        printf("opcao invalida\n");
        break;
    }
    system("pause");
    system("cls");
    }while( opcoes !='6' );
      
}
  
//=================================EXIBIR=====================================
void menuExibir ( ) {
    system("cls");
    char opcoes;
      
    do { 
        printf("[1]\t Exibir todas Contas\n[2]\t Exibir Conta especifica\n");
        printf("[3]\t Exibir todos historicos\n[4]\t Exibir historico especifico\n");
        printf("[5]\t Exibir todas operacoes\n[6]\t Exibir Operacoes por data\n");
        printf("[0]\t Voltar\n");
        scanf("%s",&opcoes);
           
    switch ( opcoes ) {
        case '1' :
            consultarContaCliente ( );
            break;
        case '2' :
            exibirContaEspecifica ( );             
            break;
        case '3' :
            consultarHistorico ( ); 
            break;
        case '4' :
            historicoExpecifico( );
            break;          
        case '5' :
            listarTodasOpercaoes ( );
            break;
        case '6' :
			exibirPorDatas ( );
			break;    
        case '0' :
            menu( );
            break;          
        default :
            printf("opcao invalida\n");
            break;
        }
        }while( opcoes !='5' ); 
}
/*---------------------------------------------------------------------------*/
// funcao responsavel de printar as informacoes da conta
void exibir ( int pos ) {
    printf("=========================\n");
    printf("Conta: %d\n",client[pos].codigo);
    printf("descricao %s\n",client[pos].descricao); 
    printf("\n");
}
 
// exibi apenas a conta que o usuario pesquisar 
void exibirContaEspecifica ( ) {
    int pos = 0, conta, ok=0;
   
    printf("\nEntre com o codigo da conta\n");
    scanf("%d",&conta);
   
    system("cls");
      
    for( pos = 0; pos < contador; pos++ ) {
        if( conta == client[pos].codigo ) {
            if( client[pos].status == 1 ) {
                exibir ( pos ); 
                ok=1;
            }
        }
    }
    if ( ok != 1 ) {
        printf("Conta nao encontrada\n");
    }
    system ("pause");
    system("cls");
    menuExibir ( );
} 
  
//exibir todas as contas cadastradas 
void consultarContaCliente( ) { 
     int pos=0; 
    for ( pos = 0; pos < contador; pos++ ) {
        if ( client[pos].status == 1 ) {
            exibir ( pos ); 
        }
    }
    if ( pos > contador ){
        printf("Nao a contas cadastradas\n");
    }
      
    system ("pause");
    system("cls");
    menuExibir ( );
}
/*----------------------------------------------------------------------------*/
//funcao responsavel de printar as informacoes do historico
void exibirHistorico ( int j ) {
      
    printf("=========================\n");
    printf("Conta: %d\n",historico[j].codigo);
    printf("descricao %s\n",historico[j].descricao);
    printf("Tipo operacao %c",historico[j].tipoDeTransacao);
    printf("\n");
      
}
 
//Exibir todo historico cadastrado
void consultarHistorico( ) { 
    int j, ok=0;
    for ( j = 0; j < his; j++ ) {
        if( historico[j].status == 1 ) {
            ok=1;
            exibirHistorico ( j );  
        }
    }
    if ( ok != 1 ) {
        printf("Sem historicos cadastrados\n");
    }
    system("pause");
}
 
//Exibir historico expecifico
void historicoExpecifico( ) { 
    int j, codigo, ok=0;
      
    printf("Codigo do historico\n");
    scanf("%d",&codigo);
      
    for ( j = 0; j < his; j++ ) {
        if( codigo == historico[j].codigo ) {
            if( historico[j].status == 1 ) {
            ok = 1;
            exibirHistorico ( j );  
            }
        }
    }
    if ( ok != 1 ) {
        printf("Historico nao encontrado\n");
    }
    system("pause");
    menuExibir ( );
}
/*----------------------------------------------------------------------------*/ 
 // printar as informacoes das operacoes
void exibirOperacao ( int i ) {
	printf("Codigo da operacao: %d\n",movimentacao[i].cod);
    printf("Descricao \t %s \n", movimentacao[i].historico.descricao);
    printf("Data \t %d/ %d/%d \n",
            movimentacao[i].data.dia,
            movimentacao[i].data.mes,
            movimentacao[i].data.ano
    );

    printf("Tipo \t %c \n",movimentacao[i].historico.tipoDeTransacao);
    printf("Complemento \t %s \n", movimentacao[i].complemento);
    printf("Valor \t %.2f \n", movimentacao[i].valor);
    printf(" \n \n");
}
 
// exibir informacoes da conta expecifica   
void listarMovimentacoes ( ) {
    system("cls"); 
    char descricaoTipo[20];
    int i;
   
    if( movi > 0 ) {
        printf(" \n Lista de Movimentacoes \n \n");
        for( i = 0; i < movi; i++ ) {
            if( movimentacao[i].client.codigo == dadosClient(statusConta).codigo ) {
            	exibirOperacao ( i );
            }
        }
    }else{
        printf("Nenhuma operacao realizada!\n");   
    }
    system("pause");
    system("cls");
    menu( );
}
 
// exibir informacoes de todas as contas  
void listarTodasOpercaoes ( ) {
    system("cls"); 
    char descricaoTipo[20];
    int i;
   
    if( movi > 0 ) {
        printf(" \n Lista de Movimentacoes \n \n");
        for( i = 0; i < movi; i++ ) {
            if(movimentacao[i].status == 1){
                exibirOperacao ( i );
            }
        }
    }else{
        printf("Nenhuma operacao realizada!\n");   
    }
    system("pause");
    system("cls");
    menuExibir ( );
  
}

void exibirPorDatas ( ) {
	system("cls"); 
    char descricaoTipo[20];
    int i, j;
    int dia, mes, ano;
    if( movi > 0 ) {
		printf("Informe a data d opercao que deseja procurar: \n");
		printf("Dia:\n");
		scanf("%d", &dia);
		
		printf("Mes:\n");
		scanf("%d", &mes);
		
		printf("Ano:\n");
		scanf("%d", &ano);
		
		for ( j = 0; j < movi; j++ ) {
			
			if ( dia == movimentacao[j].data.dia && mes == movimentacao[j].data.mes && ano == movimentacao[j].data.ano ) {
				printf(" \n Lista de Movimentacoes do dia \n \n");
				exibirOperacao ( j );
			}
		}
	}
	else {
        printf("Nenhuma operacao realizada!\n");   
    }
    system("pause");
    system("cls");
    menuExibir ( );
}
  
//===============================EXCLUIR===================================
void menuExcluir ( ) {
    system("cls");
    char opcoes;
      
    do { 
        printf("[1]\t Excluir Conta\n");
        printf("[2]\t Excluir historico\n");
        printf("[3]\t Excluir operacoes\n");
        printf("[0]\t Voltar\n");
        scanf("%s",&opcoes);
           
    switch ( opcoes ) {
        case '1' :
            excluirContaCliente( );
            break;
        case '2' :
            excluirHistorico( );             
            break;
        case '3' :
            excluirOperacao( ); 
            break;
        case '0' :
            menu ( );
            break;          
        default :
            printf("opcao invalida\n");
            break;
        }
        system("pause");
        system("cls");
        }while( opcoes !='5' ); 
}
 
//Excluir conta
void excluirContaCliente( ) {
    int cod, i, j, ok=0;
    char resp;
  
    printf("Codigo da Conta\n");
    scanf("%d", &cod );
     
    for( i=0; i < contador; i++ ) {
        if( client[i].codigo == cod ) {
            ok = 1;
            exibir ( i );
             
            getchar();
             
            printf("\nDeseja realmente exlucir? S/N:");
            scanf("%c",&resp);
            if ( ( resp == 'S' ) || ( resp == 's' ) ) {
                for( j=i; j<contador-1; j++ ) {
                client[j].codigo = client[j+1].codigo;
                strcpy(client[j].descricao, client[j+1].descricao);
                }
                contador--;
                printf("\nExclusao feita com sucesso\n");
                break;
            } 
            else {
                    if ( ( resp == 'N' ) || ( resp == 'n' ) ) {
                        printf("Exclusao cancelada!\n");
                        break;
                    }
                }
            }
        }
        if (ok!=1){
        printf("Conta nao encontrada!\n");
        }
  
  
  
    system("pause");
    system("cls");
  
}

//Excluir historico 
void excluirHistorico( ) {
    int cod, i, j, ok=0;
    char resp;
  
    printf("Codigo da Operacao\n");
    scanf("%d", &cod );
     
    for( i=0; i < his; i++ ) {
        if( historico[i].codigo == cod ) {
            ok = 1;
            exibirHistorico ( i );
             
            getchar();
             
            printf("\nDeseja realmente exlucir? S/N:");
            scanf("%c",&resp);
            if ( ( resp == 'S' ) || ( resp == 's' ) ) {
                for( j=i; j<his-1; j++ ) {
                historico[j].codigo = historico[j+1].codigo;
                strcpy(historico[j].descricao, historico[j+1].descricao);
                historico[j].tipoDeTransacao == historico[j+1].tipoDeTransacao;
                }
                movi--;
                printf("\nExclusao feita com sucesso\n");
                break;
            } 
            else {
                    if ( ( resp == 'N' ) || ( resp == 'n' ) ) {
                        printf("Exclusao cancelada!\n");
                        break;
                    }
                }
            }
        }
        if (ok!=1){
        printf("Operacao nao encontrado!\n");
        }
  
  
  
    system("pause");
    system("cls");
  
}

//Excluir operacoes 
void excluirOperacao( ) { 
    int cod, i, j, ok=0;
    char resp;
  
    printf("Codigo do historico\n");
    scanf("%d", &cod );
     
    for( i=0; i < movi; i++ ) {
        if( i == cod ) {
            ok = 1;
                exibirOperacao ( i );
             
            getchar();
             
            printf("\nDeseja realmente exlucir? S/N:");
            scanf("%c",&resp);
            if ( ( resp == 'S' ) || ( resp == 's' ) ) {
                for( j=i; j < movi-1; j++ ) {
                     
                movimentacao[j].cod = movimentacao[j+1].cod;
                strcpy(movimentacao[j].historico.descricao, movimentacao[j+1].historico.descricao);
                 
                movimentacao[j].data.dia = movimentacao[j+1].data.dia;
                movimentacao[j].data.mes = movimentacao[j+1].data.mes;
                movimentacao[j].data.ano = movimentacao[j+1].data.ano;
                movimentacao[j].historico.tipoDeTransacao = movimentacao[j+1].historico.tipoDeTransacao;                    
                strcpy(movimentacao[j].complemento, movimentacao[j+1].complemento);
                movimentacao[j].valor = movimentacao[j+1].valor;
                 
                }
                movi--;
                printf("\nExclusao feita com sucesso\n");
                break;
            } 
            else {
                    if ( ( resp == 'N' ) || ( resp == 'n' ) ) {
                        printf("Exclusao cancelada!\n");
                        break;
                    }
                }
            }
        }
        if (ok!=1){
        printf("Operacao nao encontrada!\n");
        }
  
  
  
    system("pause");
    system("cls");
  
}
  
//==================================ALTERAR=================================
void menuAlterar ( ) {
    system("cls");
    char opcoes;
      
    do { 
        printf("[1]\t Alterar Conta\n");
        printf("[2]\t Alterar Historico\n");
        printf("[3]\t Alterar Operacoes\n");
        printf("[0]\t Volta\n");
        scanf("%s",&opcoes);
           
    switch ( opcoes ) {
        case '1' :
            alterarConta ( );
            break;
        case '2' :
            alterarHistorico ( );             
            break;
        case '3' :
        	alterarOperacao ( );
            break;
        case '0' :
            menu( );
            break;          
        default :
            printf("opcao invalida\n");
            break;
        }
        system("pause");
        system("cls");
        }while( opcoes !='5' ); 
}
 
//Alterar conta 
void alterarConta ( ) {
	int i, cod, confirmacao, ok = 0, codigo;
    char resp;
 
    printf("\nCodigo da conta: \n");
    scanf("%d",&cod );
    
    for( i = 0; i < contador; i++ ) { 
        if ( client[i].codigo == cod ) { 
            
            exibir ( i );
            
            getchar();

            printf("\nDeseja realmente Alterar? [s]/[n]:\n");
            scanf("%c",&resp);

            if ( ( resp == 'S' ) || ( resp == 's' ) ) {
            	
            	printf("Digite as novas informacoes: \n");
            	
            	printf("Codigo da Conta: \n");
            	while(ok != 1) {
            	scanf("%d",&codigo);                    
                confirmacao = verificarCod( codigo );
                    
	                if( confirmacao == 1 ) {
	                	ok = 1;
	                	client[i].codigo = codigo;
					}
					if (ok != 1){
						printf("\nCodigo ja existente\n");
					}
				}
                                
                printf("\nNova Descricao: \n");
                fflush(stdin);
            	gets(client[i].descricao);
            	
                printf("\nAlteracao feita com sucesso\n");
                break;
            }
            else {
                if ( ( resp == 'N' ) || ( resp == 'n' ) ) {
                    printf("Alteracao cancelada!\n");
                    break;
                }
            }
        }
        if ( i > contador )
            printf("\nCodigo nao encontrado\n");
    }
    system("pause");
    system("cls");
}

//Alterar historico
void alterarHistorico ( ) {
	int i, cod, confirmacao, ok = 0, codigo;
    char resp, op;
 
    printf("\nCodigo do Historico: \n");
    scanf("%d",&cod );
    
    for( i = 0; i < his; i++ ) { 
        if ( historico[i].codigo == cod ) { 
            
            exibirHistorico ( i );
            
            getchar();

            printf("\nDeseja realmente Alterar? [s]/[n]:\n");
            scanf("%c",&resp);

            if ( ( resp == 'S' ) || ( resp == 's' ) ) {
            	
            	printf("Digite as novas informacoes: \n");
            	
            	printf("Codigo do Historico: \n");
            	while(ok != 1) {
            	scanf("%d",&codigo);                    
                confirmacao = verificarCodHistorico( codigo );
                    
	                if( confirmacao == 1 ) {
	                	ok = 1;
	                	client[i].codigo = codigo;
					}
					if (ok != 1){
						printf("\nCodigo ja existente\n");
					}
				}
                                
                printf("\nNova Descricao: \n");
                fflush(stdin);
            	gets(historico[i].descricao);
            	
            	printf("[c]\tCredito\n[d]\tDebito\n");
     
			    while( 1 ) {
			        scanf("%s",&op);
			        setbuf(stdin, NULL);
			        if( op == 'C' || op == 'c' ) {
			            historico[i].tipoDeTransacao = 'c';
			            break;
			        }
			        if( op == 'D' || op == 'd' ) {
			            historico[i].tipoDeTransacao = 'd';
			            break;
			        }
			        else{
			            printf("Operacao invalida\n");
			        }
			        }
            	
                printf("\nAlteracao feita com sucesso\n");
                break;
            }
            else {
                if ( ( resp == 'N' ) || ( resp == 'n' ) ) {
                    printf("Alteracao cancelada!\n");
                    break;
                }
            }
        }
        if ( i > his )
            printf("\nCodigo nao encontrado\n");
    }
    system("pause");
    system("cls");
}

//Alterar operecao
void alterarOperacao ( ) {
	int i, cod, codigo ;
    char resp, op;
    int codigoOperacao, dia, mes, ano ;
    int operacaoEncontrada = 0, verificar;
	float valorMovimentacao;
 
    printf("\nCodigo da operacao: \n");
    scanf("%d",&cod );
    
    for( i = 0; i < movi; i++ ) { 
        if ( movimentacao[i].cod == cod ) { 
            
            exibirOperacao ( i );
            
            getchar();

            printf("\nDeseja realmente Alterar? [s]/[n]:\n");
            scanf("%c",&resp);

            if ( ( resp == 'S' ) || ( resp == 's' ) ) {
            	
            	printf("Digite as novas informacoes: \n");
            	
            	printf("Codigo da movimentacao: %d \n",movimentacao[i].cod );
                                
			    printf("Historicos:\n");
			    consultarHistorico( );
			      
			    printf("\nCodigo do historico: \n");
			    scanf("%d",&codigoOperacao);
			      
			    operacaoEncontrada = buscaHistorico(codigoOperacao);
			    movimentacao[i].historico = historico[(operacaoEncontrada)];
			    movimentacao[i].client = dadosClient (statusConta);
			  
			    printf("Valor: \n");
			    scanf("%f",&movimentacao[i].valor);
			  
			    printf("Data dd/mm/aa\n");
			    printf("Dia: ");
			    scanf("%d",&dia);
			    printf("Mes: ");
			    scanf("%d",&mes);
			    printf("Ano: ");
			    scanf("%d",&ano);
			    
			    movimentacao[i].data.dia = dia;
			    movimentacao[i].data.mes = mes;
			    movimentacao[i].data.ano = ano;
			    
			    verificar = verificarData( dia, mes, ano );
				if(verificar){
					printf("Limite para esse dia excedido!!\n");
					return;
				}
			  
			    printf("Complemento: \n");
			    scanf("%s",&movimentacao[i].complemento);
			     
			    movimentacao[i].status = 1;
            	
                printf("\nAlteracao feita com sucesso\n");
                break;
            }
            else {
                if ( ( resp == 'N' ) || ( resp == 'n' ) ) {
                    printf("Alteracao cancelada!\n");
                    break;
                }
            }
        }
        if ( i > movi )
            printf("\nOperacao nao encontrado\n");
    }
    system("pause");
    system("cls");
}

//========================Cadastra informa�oes==================================
//cadastra cliente        
void cadastraConta( int codigo, int i ) {
    system("cls");
    i = verificarPosicao( );   
      
    client[i].codigo = codigo;
      
          
    printf("Conta: %d\n",client[i].codigo);
          
    printf("descricao\n");
    scanf("%s",&client[i].descricao);
         
    client[i].status = 1; 
       
    contador++;
         
    printf("\nCadastro Realizado com Sucesso!\n\n");
    getchar();
       
    system ("pause");
    system("cls");
    main ( );       
}

// cadastra historico       
void cadastraHistorico ( int codigo, int j ) {
    system("cls");
    int ok;
    char op;
  
    j = verificarPosicaoHistorico ( );
    historico[j].codigo = codigo; 
      
    printf("Codigo: %d\n",historico[j].codigo);
      
    printf("Descricao:\n");
    scanf("%s",&historico[j].descricao);
        
    printf("[c]\tCredito\n[d]\tDebito\n");
     
    while( 1 ) {
        scanf("%s",&op);
        setbuf(stdin, NULL);
        if( op == 'C' || op == 'c' ) {
            historico[j].tipoDeTransacao = 'c';
            break;
        }
        if( op == 'D' || op == 'd' ) {
            historico[j].tipoDeTransacao = 'd';
            break;
        }
        else{
            printf("Operacao invalida\n");
        }
        }
      
    historico[j].status =1;
         
    printf("\nOpercao feita com sucesso\n");
      
    movimentacao[j].historico = historico[(ok - 1)];
    //codigo = movimentacao[j].client;
    his++;  
           
    system("pause");
    system("cls");
    main( );
}  

//cadastra as movimentacoes
void realizarOperacoes  ( ) {
    system("cls"); 
    int codigoOperacao, dia, mes, ano, i, j, ok=0;
    int operacaoEncontrada = 0, verificar;
	float valorMovimentacao;
	
    movimentacao[movi].cod = movi; 
    printf("Codigo operacao: %d\n",movimentacao[movi].cod);
    
	 
    printf("Historicos:\n");
    consultarHistorico( );
      
    printf("\nCodigo do historico: \n");
    scanf("%d",&codigoOperacao);
      
    operacaoEncontrada = buscaHistorico(codigoOperacao);
    movimentacao[movi].historico = historico[(operacaoEncontrada)];
    movimentacao[movi].client = dadosClient (statusConta);
  
    printf("Valor: \n");
    scanf("%f",&movimentacao[movi].valor);
  
    printf("Data dd/mm/aa\n");
    printf("Dia: ");
    scanf("%d",&dia);
    printf("Mes: ");
    scanf("%d",&mes);
    printf("Ano: ");
    scanf("%d",&ano);
    
    movimentacao[movi].data.dia = dia;
    movimentacao[movi].data.mes = mes;
    movimentacao[movi].data.ano = ano;
    
    verificar = verificarData( dia, mes, ano );
	if(verificar){
		printf("Limite para esse dia excedido!!\n");
		return;
	}
  
    printf("Complemento: \n");
    scanf("%s",&movimentacao[movi].complemento);
     
    movimentacao[movi].status = 1;
      
    movi++;
    printf("\nOpercao feita com sucesso!!\n");
          
    system("pause"); 
    system("cls");       
    menu( );
}

//============================fun�oes diversas===================================
// verifica se ainda eh possivel fazer opera�oes por data
int verificarData( int dia, int mes, int ano ) {
	int data = 1, i;
	
	if( movi > 0 ) {
		for( i = 0; i < movi; i++ ) {
			if( movimentacao[i].data.dia == dia &&
			    movimentacao[i].data.mes == mes &&
			    movimentacao[i].data.ano == ano ){

				data++;
			}
		}
	}

	if( data <= QTDMAXDIA ) {
		return 0; // n�o excedeu 
	}
	return 1; // excedeu 
}

// valida entrada da na conta do client 
void login ( ) {
    system("cls");
    int codigoDaConta;
    int i;
      
    printf("Digite sua conta \n\n");
    scanf("%d", &codigoDaConta);
      
    if( contador > 0 ) {
        for( i = 0; i < contador; i++ ) {
            if( client[i].codigo == codigoDaConta ) {
                statusConta = client[i].codigo;
                menu ( );
                break;
            }
        }
        if( statusConta == 0 ) {
            printf(" Conta nao encontrada \n \n ");
            system("pause");
            login ( );
            }
        }
   
    else {
        printf(" Nao  possui nenhuma conta cadastrada \n \n");
    }
}

//busca a posicao do historico 
int buscaHistorico( int codigo ) {
    int i;
      
    for( i = 0; i < TAMH; i++ ) {
        if( historico[i].codigo == codigo) {
            return i;
        }
    }
    return 0;
}

// associa a posi��o da conta client as opera�oes  
Client dadosClient ( int conta ) {
    int i;
    for ( i = 0; i < TAMH; i++ ) {
        if( conta == client[i].codigo ) {
            return client[i];
        }
    }
}
  
//exibi saldo
float processarOpercao ( ) {
    float saldo = 0;
	float cred = 0, deb = 0;
    for(int h = 0 ; h < movi; h++){
        if(movimentacao[h].client.codigo == dadosClient(statusConta).codigo){
            if(movimentacao[h].historico.tipoDeTransacao == 'd'){
                saldo -= movimentacao[h].valor;
                deb -= movimentacao[h].valor;
            }else{
                saldo += movimentacao[h].valor;
                cred += movimentacao[h].valor;
            }
        }
    }
    printf("\nSaldo atual: R$ %.2f.\n", saldo);
    printf("Total credito %.2f\n",cred);
    printf("Total debito %.2f\n",deb);
    system("pause");
    system("cls");
    menu();
} 
     
//Verifica se a posicao  do vetor ja foi preenchida por alguma historico
int verificarPosicaoHistorico ( ) { 
    int j;
    for( j = 0; j < TAMH; j++ ) {
        if ( historico[j].status == 0 ) {
            return(j);
        }
    }
    return(-1);
} 
       
//Verifica se o historico ja foi cadastrado
int verificarCodHistorico ( int codigo ) {
    int j;
     for( j = 0; j < his; j++ ) {
        if ( historico[j].codigo == codigo ) {
            return(0);
        }
    }
     return(1);
}
  
//Verifica se a posicao  do vetor ja foi preenchida por alguma conta
int verificarPosicao ( ) { 
    int i;
    for( i = 0; i < TAMC; i++ ) {
        if ( client[i].status == 0 ) {
            return(i);
        }
    }
    return(-1);
} 
           
//Verifica se o conta ja foi cadastrado
int verificarCod( int codigo ) {
    int i;
     for( i = 0; i < contador; i++ ) {
        if ( client[i].codigo == codigo ) {
            return(0);
        }
    }
     return(1);
}
