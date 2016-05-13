%This will display the four different waves that we can expect.
%Ensure that the 4 waves from resources folder are in local directory.
%Preliminary analysis can be done on this data. Using Matlab because reasons.

a = csvread('wave1.txt');
plot(a(:,1), a(:,2));
figure;
b = csvread('wave2.txt');
plot(b(:,1), b(:,2));
figure;
c = csvread('wave3.txt');
plot(c(:,1), c(:,2));
figure;
d = csvread('wave4.txt');
plot(d(:,1), d(:,2));
