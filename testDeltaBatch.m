% Treinamento para o d�gito 0 utilizando o m�todo Batch

clear all
clc

% Entradas em forma de matrizes 1x7 para cada um dos d�gitos poss�veis
X = [1 1 1 1 1 1 0;
     0 1 1 0 0 0 0;
     1 1 0 1 1 1 1;
     1 1 1 1 0 0 1;
     0 1 1 0 0 1 1;
     1 0 1 1 0 1 1;
     1 0 1 1 1 1 1;
     1 1 1 0 0 0 0;
     1 1 1 1 1 1 1;
     1 1 1 1 0 1 1];

% Sa�das desejadas, n�vel alto apenas para o d�gito 0
D = [0; 0; 0; 0; 0; 0; 0; 0; 0; 1];

W = 2*rand(1, 7) - 1;   % Inicializa��o dos sete pesos

% Treinamento (ajuste de pesos):
for epoch = 1:40000
    W = DeltaBatch(W, X, D);
end

%Inference:
N = 10;
y = zeros(N,1);
for k = 1:N
    x = X(k, :)';
    v = W*x;
    y(k) = Sigmoid(v);  % Sa�da obtida
end

disp('Results:');
disp('   [desired   neuron_output]');
disp([D y]);
disp(W)
