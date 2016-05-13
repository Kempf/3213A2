%This will display the four different waves that we can expect.
%Ensure that the 4 waves from resources folder are in local directory.
%Preliminary analysis can be done on this data. Using Matlab because reasons.



%Pulses vary in width. 0.010 seconds is one... Assuming this is roughly the
%smallest size. Haven't checked further.
%Time steps of the waves is 20us. So there are ~500 bits of data for each
%pulse. - This is relevant for power calculations.


%%%%%%%%%%%%      OBSERVATIONS FROM THIS CODE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Differentiation gives a little insight, but it doesn't detect triangles very well. 
% This is due to their relatively small gradient. Sampling would improve this.
% If noise is present, it's completely useless.
%
% Integration works for all cases - This uses sampling, every... 1ms. It picks up on
% all different shapes, regardless of noise.
% The peaks also have different magnitudes for each shape - Circle > Triangle > Inverse Circle,
% assuming the same width.
% However, different widths makes this slightly unreliable. 
% It MAY* work on it's own using thresholds, but this is yet to be seen. This could be worth testing.
% One possibility would be to combine
% these two methods of analysis (If the chip has enough computation power &/or memory. 
% Basically, if pulse is detected, check differentiation to determine what it was. 
% This would be decent, unless noise is present.
% To avoid noise, might need to do something else. 
%
% This is just some interim analysis.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%I also have added a rough multiplication by 1024 to simulate the ADC system. Noise makes that a bit interesting.




clear all;
close all;


%Wave1 only shows curved pulses.
a = 1024 .* csvread('wave1.txt');
subplot(3,1,1);
plot(a(:,1), a(:,2));
subplot(3,1,2);
%Differentiation Method
td = a(2,1) - a(1,1);
dx = a(:,1) + (td/2);
n = size(a);
dx(n(1)) = [];
plot(dx, diff(a(:,2)));
subplot(3,1,3);
%Integration Method (POWERRRRRRRRRR)
w1_int = zeros(n(1),1);
for n = 501:1500001
    for p = 0:50:500
        q = n - p;
        w1_int(n) = w1_int(n) + (a(q, 2)^2/(50*td));
    end
end
x_int = a(:,1);
for n = 500:-1:1
   x_int(n) = []; 
   w1_int(n) = [];
end
plot(x_int, w1_int);


%Includes all 3. Derivation of wide triangles is pretty shitty. They are
%very difficult to notice. Zoom in on lower plot at 3.27 seconds.
figure;
b = 1024 .* csvread('wave2.txt');
subplot(3,1,1);
plot(b(:,1), b(:,2));
subplot(3,1,2);
td = b(2,1) - b(1,1);
dx = b(:,1) + (td/2);
n = size(b);
dx(n(1)) = [];
plot(dx, diff(b(:,2)));
subplot(3,1,3);
%Integration Method (POWERRRRRRRRRR)
w2_int = zeros(n(1),1);
for n = 501:1500001
    for p = 0:50:500
        q = n - p;
        w2_int(n) = w2_int(n) + (b(q, 2)^2/(50*td));
    end
end
x_int = b(:,1);
for n = 500:-1:1
   x_int(n) = []; 
   w2_int(n) = [];
end
plot(x_int, w2_int);





figure;
c = 1024 .* csvread('wave3.txt');
subplot(3,1,1);
plot(c(:,1), c(:,2));
subplot(3,1,2);
td = c(2,1) - c(1,1);
dx = c(:,1) + (td/2);
n = size(c);
dx(n(1)) = [];
plot(dx, diff(c(:,2)));
subplot(3,1,3);
%Integration Method (POWERRRRRRRRRR)
w3_int = zeros(n(1),1);
for n = 501:1500001
    for p = 0:50:500
        q = n - p;
        w3_int(n) = w3_int(n) + (c(q, 2)^2/(50*td));
    end
end
x_int = c(:,1);
for n = 500:-1:1
   x_int(n) = []; 
   w3_int(n) = [];
end
plot(x_int, w3_int);



%Differentiation does not work for high signal noise. Needs a new method.
figure;
d = 1024 .* csvread('wave4.txt');
subplot(3,1,1);
plot(d(:,1), d(:,2));
subplot(3,1,2);
td = d(2,1) - d(1,1);
dx = d(:,1) + (td/2);
n = size(d);
dx(n(1)) = [];
plot(dx, diff(d(:,2)));
%Integration Method (POWERRRRRRRRRR)
subplot(3,1,3)
w4_int = zeros(n(1),1);
for n = 501:1500001
    for p = 0:50:500
        q = n - p;
        w4_int(n) = w4_int(n) + (d(q, 2)^2/(50*td));
    end
end
x_int = d(:,1);
for n = 500:-1:1
   x_int(n) = []; 
   w4_int(n) = [];
end
plot(x_int, w4_int);
