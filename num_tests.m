format compact
format shortg
clc, clear, close all

r = -0.5;
x = 4

figure, hold on
for i = 1:15
    
    plot(i, x, 'b.')
    
    if x > 0
        x = x + r*x
    else
        x = 0
    end
end
