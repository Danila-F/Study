clc;
clear;
close all;

load('dataset.mat');

%% datasets

N = length(targets);

N_inputs = size( inputs, 1 );
N_outputs = 10;

% tr_data_ext - расширенный набор данных для обучения
% tr_targets - метки классов набора данных для обучения

% test_data_ext - расширенный набор данныхдля теста
% test_targets - метки классов набора данных для теста

%% create NN
lr = 1e-3;

NN = {};

% NN{1} = Dense( *, N_inputs, lr );
% NN{2} = sigmoid();
% ...
% NN{*} = Dense( N_outputs, *, lr );
% NN{*} = softmax();

%% training
epochs = 100;

batch_size = 32;
shuffle_ind = randperm(N_training);
shuffled_N = floor(N_training / batch_size);

test_log = zeros( 1, epochs );
tr_log = zeros( 1, shuffled_N * epochs );

for i = 1:epochs
    for j = 1:shuffled_N
        batch_slice = batch_size*(j-1)+1:batch_size*j;
        E = E_logloss( tr_targets( :, shuffle_ind(batch_slice)));
        tr_log(shuffled_N*(i-1)+j) = training( NN, E, tr_data_ext( :, shuffle_ind(batch_slice)));
    end
    
    test_log(i) = testing(NN, test_data_ext, test_targets);
end

test_log(end)

%%
t = tiledlayout(1,1);
ax1 = axes(t);
plot(ax1,test_log,'-r')
ax1.XColor = 'r';
ax1.YColor = 'r';

ax2 = axes(t);
plot(ax2,tr_log,'-k')
ax2.XAxisLocation = 'top';
ax2.YAxisLocation = 'right';
ax2.Color = 'none';
ax1.Box = 'off';
ax2.Box = 'off';



