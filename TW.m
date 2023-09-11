parametros_maquina;
%
%
% Simulacion
%
disp('');
disp('Espere unos instantes.....simulacion en progreso')
tic;
sim('sim21',3);
toc
disp('');
disp('Simulacion finalizada')

% ia = maq(:,1);

figure
subplot(3,2,1);
plot(t,maq(:,2));
title('i_{qs}');
xlabel('Tiempo [s]');
grid on;
subplot(3,2,2);
plot(t,maq(:,3));
title('i_{ds}');
xlabel('Tiempo [s]');
grid on;
subplot(3,2,3);
plot(t,maq(:,5));
title('{\psi}_{qs}');
xlabel('Tiempo [s]');
grid on;
subplot(3,2,4);
plot(t,maq(:,6));
title('{\psi}_{ds}');
xlabel('Tiempo [s]');
grid on;
subplot(3,2,5);
plot(t,maq(:,7));
title('{\psi}_{qr}');
xlabel('Tiempo [s]');
grid on;
subplot(3,2,6);
plot(t,maq(:,8));
title('{\psi}_{dr}');
xlabel('Tiempo [s]');
grid on;

figure
subplot(2,2,[1,2]);
plot(maq(:,4)*wb*60/(2*pi),maq(:,1))
title('Tem vs w');
xlabel('Velocidad [rpm]');
ylabel('Torque [Nm]');
grid on;
subplot(2,2,3);
plot(t,maq(:,4)*wb*60/(2*pi));
title('wr');
xlabel('Tiempo [s]');
grid on;
subplot(2,2,4);
plot(t,maq(:,1));
title('Tem');
xlabel('Tiempo [s]');
grid on;

figure
subplot(2,2,[1,2]);
plot(t,Vdq(:,1));
title('V_{ds}')
xlabel('Tiempo [s]');
grid on;
subplot(2,2,3);
plot(t,Vdq(:,2));
title('V_{qs}')
xlabel('Tiempo [s]');
grid on;
subplot(2,2,4);
plot(t,Vdq(:,3));
title('V_{0s}')
xlabel('Tiempo [s]');
grid on;



