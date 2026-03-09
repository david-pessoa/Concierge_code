# Concierge
Código do programa que controla o carrinho Concierge desenvolvido na discplina de Circuitos Elétricos e Eletrônicos da faculdade de Ciências da Computação.
O Concierge é um carrinho robótico projetado para transportar pequenos objetos para o usuário, sendo controlado remotamente através de um aplicativo de controle virtual no celular via Bluetooth.  

## Objetivo
O objetivo do projeto é demonstrar a integração entre sistemas embarcados, sensores, motores e comunicação sem fio, criando um sistema automatizado capaz de auxiliar no transporte de cargas.
O carrinho possui uma balança integrada na parte superior, permitindo monitorar o peso dos itens transportados. Caso o peso ultrapasse o limite estabelecido de 1,5 kg, o sistema alerta o usuário por meio de mensagens exibidas em um display LCD.

## Componentes
| Componente                          | Função                                                       |
| ----------------------------------- | ------------------------------------------------------------ |
| Arduino UNO                         | Microcontrolador responsável por controlar todo o sistema    |
| Módulo Bluetooth HC-05              | Comunicação entre o celular e o carrinho                     |
| Motores DC                          | Responsáveis pela movimentação do carrinho                   |
| Driver de motor (ponte H)           | Controle da direção de rotação dos motores                   |
| Display LCD 20x4 com interface I2C  | Exibição de mensagens e informações do sistema               |
| Célula de carga                     | Sensor responsável por medir o peso                          |
| HX711                               | Amplificador e conversor A/D para leitura da célula de carga |
| Bateria LiPo                        | Alimentação dos motores e do sistema                         |

## Bibliotecas Utilizadas
```
LiquidCrystal_I2C
HX711
SoftwareSerial
```
### LiquidCrystal_I2C
Responsável por controlar o display LCD utilizando comunicação I2C, reduzindo o número de pinos necessários.

### HX711
Biblioteca utilizada para comunicação com o módulo HX711, responsável por ler e converter os sinais da célula de carga.

### SoftwareSerial
Permite criar uma porta serial em pinos digitais para comunicação com o módulo Bluetooth.

## Mapeamento dos pinos do Arduino
| Pino | Componente         |
| ---- | ------------------ |
| 2    | HX711 (DT)         |
| 3    | HX711 (SCK)        |
| 5    | Bluetooth RX       |
| 6    | Bluetooth TX       |
| 10   | Motor (controle 1) |
| 9    | Motor (controle 2) |
| 8    | Motor (controle 3) |
| 7    | Motor (controle 4) |


## Funcionamento
O funcionamento do Concierge baseia-se na recepção de comandos enviados por um aplicativo de controle remoto no celular via Bluetooth. Esses comandos são interpretados pelo Arduino, que executa ações como movimentar o carrinho ou realizar a leitura da balança.
Quando o sistema é iniciado, o Arduino executa o método setup(), responsável por:
- Inicializar o display LCD
- Inicializar o módulo HX711
- Calibrar a balança
- Iniciar a comunicação serial
- Iniciar a comunicação Bluetooth
- Configurar os pinos responsáveis pelo controle dos motores

Após essa etapa, o programa entra no loop principal, onde permanece continuamente verificando se há comandos disponíveis vindos do módulo Bluetooth.
Quando um comando é recebido, ele é armazenado na variável comando e interpretado através de uma estrutura switch, que define qual ação deve ser executada.
A partir dos comandos enviados pelo controle virtual, é possível movimentar o carrinho para frente, direita, esquerda, trás ou recalcular o peso sobre a balança.
```
EXCESSO DE PESO!
POR FAVOR, RETIRE
O EXCESSO DE PESO!
```
Caso contrário, o display informará a quantidade de peso sobre o Concierge:
```
Peso em kg: (peso)
```

### Comandos do controle
Os comandos recebidos via Bluetooth correspondem aos seguintes caracteres:
| Comando     | Ação                          |
| ----------- | ----------------------------- |
| F           | Move o carrinho para frente   |
| B           | Move o carrinho para trás     |
| L           | Move o carrinho para esquerda |
| R           | Move o carrinho para direita  |
| W           | Ativa a leitura da balança    |
| Outro valor | Para o carrinho               |

### Controle dos motores
Os motores são controlados através de quatro pinos digitais conectados ao driver de motor.
Cada função do programa altera o estado lógico desses pinos utilizando `digitalWrite()`, permitindo controlar o sentido de rotação dos motores e, consequentemente, a direção do carrinho.
As funções responsáveis pelo controle de movimento são:
- moveFrente() → movimenta o carrinho para frente
- moveRe() → movimenta o carrinho para trás
- direita() → realiza curva para direita
- esquerda() → realiza curva para esquerda
- parar() → interrompe o movimento do carrinho

## Sistema de Pesagem
O módulo conversor e amplificador HX711 de 24 bits é utilizado para amplificar o sinal proveniente da célula de carga, permitindo que o Arduino consiga interpretar as variações de peso.
A função `ativa_balanca()` realiza a leitura do peso utilizando:
```
scale.get_units()
```

Esse valor é convertido para quilogramas com base no fator de calibração definido no código.
Após a leitura, o sistema verifica se o peso ultrapassa o limite estabelecido de 1,5 kg.
- Se o peso for maior que 1,5 kg, o display exibe um alerta de excesso de carga.
- Se o peso estiver dentro do limite, o display apresenta o valor medido.
Essa funcionalidade garante que o carrinho não transporte cargas acima do limite definido para o projeto.

## Fluxo de Execução
1. O funcionamento geral do sistema pode ser resumido da seguinte forma:
2. O Arduino inicializa todos os componentes do sistema.
3. O sistema aguarda comandos enviados via Bluetooth.
4. O usuário envia comandos através do aplicativo no celular.
5. O Arduino interpreta o comando recebido.
5. O sistema executa a ação correspondente: movimentar o carrinho, medir o peso
6. O resultado da medição é exibido no display LCD.
