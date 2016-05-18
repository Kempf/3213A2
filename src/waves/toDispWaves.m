%This will display the four different waves that we can expect.
%Ensure that the 4 waves from resources folder are in local directory.
%Preliminary analysis can be done on this data. Using Matlab because reasons.



%Pulses vary in width. 0.010 seconds is one... Assuming this is roughly the
%smallest size. Haven't checked further.
%Time steps of the waves is 20us. So there are ~500 bits of data for each
%pulse. - This is relevant for power calculations.


clear all;
close all;


% %Wave1 only shows curved pulses.
% a = 1024 .* csvread('wave1.txt');
% subplot(3,1,1);
% plot(a(:,1), a(:,2));
% title('wave1');
% subplot(3,1,2);
% %Differentiation Method
% td = a(2,1) - a(1,1);
% dx = a(:,1) + (td/2);
% n = size(a);
% dx(n(1)) = [];
% plot(dx, diff(a(:,2)));
% title('differentiation of wave');
% subplot(3,1,3);
% %Integration Method (POWERRRRRRRRRR)
% w1_int = zeros(n(1),1);
% for n = 501:1500001
%     for p = 0:50:500
%         q = n - p;
%         w1_int(n) = w1_int(n) + (a(q, 2)^2/(50*td));
%     end
% end
% x_int = a(:,1);
% for n = 500:-1:1
%    x_int(n) = []; 
%    w1_int(n) = [];
% end
% plot(x_int, w1_int);
% title('Integration of wave');
% 
% 
% %Includes all 3. Derivation of wide triangles is pretty shitty. They are
% %very difficult to notice. Zoom in on lower plot at 3.27 seconds.
% figure;
% b = 1024 .* csvread('wave2.txt');
% subplot(3,1,1);
% title('wave2');
% plot(b(:,1), b(:,2));
% subplot(3,1,2);
% td = b(2,1) - b(1,1);
% dx = b(:,1) + (td/2);
% n = size(b);
% dx(n(1)) = [];
% plot(dx, diff(b(:,2)));
% title('differentiation of wave');
% subplot(3,1,3);
% %Integration Method (POWERRRRRRRRRR)
% w2_int = zeros(n(1),1);
% for n = 501:1500001
%     for p = 0:50:500
%         q = n - p;
%         w2_int(n) = w2_int(n) + (b(q, 2)^2/(50*td));
%     end
% end
% x_int = b(:,1);
% for n = 500:-1:1
%    x_int(n) = []; 
%    w2_int(n) = [];
% end
% plot(x_int, w2_int);
% title('Integration of wave');
% 
% 
% 
% 
% 
% figure;
% c = 1024 .* csvread('wave3.txt');
% subplot(3,1,1);
% plot(c(:,1), c(:,2));
% title('wave3');
% subplot(3,1,2);
% td = c(2,1) - c(1,1);
% dx = c(:,1) + (td/2);
% n = size(c);
% dx(n(1)) = [];
% plot(dx, diff(c(:,2)));
% title('differentiation of wave');
% subplot(3,1,3);
% %Integration Method (POWERRRRRRRRRR)
% w3_int = zeros(n(1),1);
% for n = 501:1500001
%     for p = 0:50:500
%         q = n - p;
%         w3_int(n) = w3_int(n) + (c(q, 2)^2/(50*td));
%     end
% end
% x_int = c(:,1);
% for n = 500:-1:1
%    x_int(n) = []; 
%    w3_int(n) = [];
% end
% plot(x_int, w3_int);
% title('Integration of wave');


%Differentiation does not work for high signal noise. Needs a new method.
figure;
d = 1024 .* csvread('wave4.txt');
subplot(3,1,1);
plot(d(:,1), d(:,2));
title('wave4');
subplot(3,1,2);
td = d(2,1) - d(1,1);
dx = d(:,1) + (td/2);
n = size(d);
dx(n(1)) = [];
plot(dx, diff(d(:,2)));
title('differentiation of wave');
%Integration Method (POWERRRRRRRRRR)
subplot(3,1,3)
w4_int = zeros(n(1),1);
th = 0;
th_latch = 0;
start = 0;
finish = 0;
circles = 0;
triangles = 0;
horns = 0;
data = zeros(1,70);
start = [];
for n = 501:1:1500001
    data(1) = [];
    %disp(size(data));
    for p = 10:10:200
            q = n - p;
            w4_int(n) = w4_int(n) + (d(q, 2)^2/(50*td));
    end    
    data(70) = w4_int(n);
    %disp(data)
    if (w4_int(n) > 10000000) 
        th = 3;
        if(th_latch < 3)
            th_latch = 3;
        end
    elseif (w4_int(n) > 5000000)
            th = 2;
            if(th_latch < 2)
                th_latch = 2;
            end
    elseif (w4_int(n) > 600000)
            th = 1;
            if(th_latch < 1)
                th_latch = 1;
                start(length(start) + 1) = n;
            end
            
    elseif((data(1) < 600000) &&   (data(11) < 600000) &&  (data(21) < 600000) &&  (data(31) < 600000) &&  (data(41) < 600000) &&  (data(51) < 600000) &&  (data(61) < 600000))
        th = 0;
        if(th_latch == 3)
           finish = n;
           th_latch = 0;
           circles = circles + 1;
        end
        
        if(th_latch == 2)
           finish = n;
           th_latch = 0;
           triangles = triangles + 1;
        end
        
        if(th_latch == 1)
           finish = n;
           th_latch = 0;
           horns = horns + 1;
        end
    end    
end
horns = horns / 2;
x_int = d(:,1);
for n = 500:-1:1
   x_int(n) = []; 
   w4_int(n) = [];
end
p = zeros(length(start));
start = (start ./ 50) + 50;
y_1mil = linspace(600000,600000,1499501);
plot(x_int, w4_int, x_int, y_1mil, 'r--', start, p, 'k*');
title('Integration of wave');
