% Compara��o do erro quadr�tico medio de ambos os metodos: GDE vs Batch.
% Para compara��o justa ambos os pesos s�o incializados com o mesmo valor

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
D = [0; 0; 0; 0; 0; 0; 0; 0; 1; 0];

E1 = zeros(1000, 1);
E2 = zeros(1000, 1);

W1 = 2*rand(1, 7) - 1;
W2 = W1;

for epoch = 1:1000              % Treinamento - 1000 intera��es
    W1 = DeltaSGD(W1, X, D);
    W2 = DeltaBatch(W2, X, D);
    es1 = 0;
    es2 = 0;
    N = 10;
    for k = 1:N
        x = X(k, :)';
        d = D(k);
        
        v1 = W1*x;
        y1 = Sigmoid(v1);
        es1 = es1 + (d - y1)^2;
        
        v2 = W2*x;
        y2 = Sigmoid(v2);
        es2 = es2 + (d - y2)^2;
    end
    E1(epoch) = es1/N;
    E2(epoch) = es2/N;
end
plot(E1, 'r', 'LineWidth', 3.0)
hold on
plot(E2, 'b:', 'LineWidth', 3.0)
xlabel('Itera��es')
ylabel('M�dia Quadr�tica dos Erros de Treinamento')
legend('GDE', 'Batch')