# EmbarcaTech_PWM_ServoMotor
Tarefa do EmbarcaTech que propôs a implementação de um sistema com a ferramenta Pico SDK para simular o controle do ângulo de um servomotor.

# Vídeo Explicativo
A seguir um vídeo explicativo sobre o projeto.

https://drive.google.com/file/d/1pf84WA5uoHOo9-sdUQq76eOhkk3j2HkY/view?usp=sharing

# Intruções
Para executar o código em questão, deve-se possuir a extensão Wokwi Simulator instalada no Visual Studio Code e acesso a placa BitDogLab. 

Acesse o arquivo diagram.json, com a extensão Wokwi Simulator instalada, para gerar o ambiente de simulação de uma placa RaspBerry Pi Pico W composto por um servomotor conectado.

Ao começar a simulação, o braço do servomotor irá permanecer na angulação de 180°, em seguida em 90° e depois em 0°, cada um permanecendo durante 5 segundos. Após isso, o braço irá realizar um movimento periódico de forma suave entre os ângulos de 0° e 180°.

Para verificar a funcionalidade do LED, será necessário a utilização da placa BitDogLab. Nela será possivel visualizar que o nível de PWM é diretamente proporcional a intesidade do LED, aumentando o nível de PWM a intesidade do LED aumenta e reduzindo o nível de PWM a intesidade do LED é reduzida.

# Composição do código
**PWM_ServoMotor.c**
- `main()`: Inicializa o PWM para o servo motor e LED, ajusta os ângulos iniciais e entra em um loop onde o servo oscila suavemente entre 0° e 180°.
- `inicializar_pwm(uint gpio)`: Configura um pino GPIO como saída PWM, define a divisão do clock e o valor de "wrap" para obter a frequência desejada.
- `ajustar_angulo(uint gpio, uint angulo)`: Define o nível PWM correspondente a 0°, 90° ou 180° para controlar o ângulo do servo motor.

# Desenvolvedor
Abel José Rocha Barros Bezerra