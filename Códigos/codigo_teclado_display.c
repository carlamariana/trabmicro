#include "main.h"

int getkey(void){
// Função para leitura do teclado matricial
	int value = 0; // Variável para armazenar o estado do pino em análise
	int pin = 0; // Variável que conterá o valor do pino a ser analisado
	int led = 0; // Variável para armazenar o estado dos pinos de 8 à 15,
	// referentes ao display de 7 segmentos, de modo a não alterar seu valor
	for(int i = 0;i<3;i++){
		// Laço para iterar sobre as linhas do teclado matricial
		led = GPIOB->ODR & 0xFF00; // Preparação da máscara
		GPIOB->ODR = led | (0x01<<i); // Atualização da entrada do teclado
		for(int j=4;j<7;j++){
			// Laço para iterar sobre as colunas do teclado
			pin = 0x01<<j;
			value = HAL_GPIO_ReadPin(GPIOB, pin); // Lendo o valor de pin
			if(value == 1){
				return j + 3*i -3;
				// A fórmula do retorno possui a seguinte lógica:
				// j sempre itera de 4 à 6
				// Se i=0, retorna j-3 (valores de 1 à 3)
				// Se i=1, retorna j (valores de 4 à 6)
				// Se i=2, retorna j+3 (valores de 7 à 9)
			}
		}
	}
	return 0; // Retorno caso nenhuma tecla tenha sido pressionada
}

void setdisplay(int value){
	// Função para exibir o valor no display de 7 segmentos
	int door = GPIOB->ODR & 0xFF; // Variável para armazenar o estado atual
	// dos primeiros oito pinos da porta B, referentes ao teclado matricial
	switch(value){
	// Realizamos um switch case para cada valor de entrada e alteramos os
	// valores de saída da porta B para exibir o valor desejado no display
	case 1:
		GPIOB->ODR = door | 0x0600;
		break;
	case 2:
		GPIOB->ODR = door | 0x5B00;
		break;
	case 3:
		GPIOB->ODR = door | 0x4F00;
		break;
	case 4:
		GPIOB->ODR = door | 0x6600;
		break;
	case 5:
		GPIOB->ODR = door | 0x6D00;
		break;
	case 6:
		GPIOB->ODR = door | 0x7D00;
		break;
	case 7:
		GPIOB->ODR = door | 0x0700;
		break;
	case 8:
		GPIOB->ODR = door | 0x7F00;
		break;
	case 9:
		GPIOB->ODR = door | 0x6F00;
		break;
	}
}
