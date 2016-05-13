%This will display the four different waves that we can expect.
%Ensure that the 4 waves from resources folder are in local directory.
%Preliminary analysis can be done on this data. Using Matlab because reasons.

clear all;
close all;


%Wave1 only shows curved pulses.
a = csvread('wave1.txt');
subplot(2,1,1);
plot(a(:,1), a(:,2));
subplot(2,1,2);
td = a(2,1) - a(1,1);
dx = a(:,1) + (td/2);
n = size(a);
dx(n(1)) = [];
plot(dx, diff(a(:,2)));


%Includes all 3. Derivation of wide triangles is pretty shitty. They are
%very difficult to notice. Zoom on in lower plot at 3.27 seconds.
figure;
b = csvread('wave2.txt');
subplot(2,1,1);
plot(b(:,1), b(:,2));
subplot(2,1,2);
td = b(2,1) - b(1,1);
dx = b(:,1) + (td/2);
n = size(b);
dx(n(1)) = [];
plot(dx, diff(b(:,2)));




figure;
c = csvread('wave3.txt');
subplot(2,1,1);
plot(c(:,1), c(:,2));
subplot(2,1,2);
td = c(2,1) - c(1,1);
dx = c(:,1) + (td/2);
n = size(c);
dx(n(1)) = [];
plot(dx, diff(c(:,2)));



%Differentiation does not work for high signal noise. Needs a new method.
figure;
d = csvread('wave4.txt');
subplot(2,1,1);
plot(d(:,1), d(:,2));
subplot(2,1,2);
td = d(2,1) - d(1,1);
dx = d(:,1) + (td/2);
n = size(d);
dx(n(1)) = [];
plot(dx, diff(d(:,2)));
