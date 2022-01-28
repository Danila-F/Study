function r = testing(NN, test_data, test_targets)
    y = forward( NN, test_data );
    [~, nn_results] = max(y, [], 1);
    r = mean(nn_results-1 == test_targets);
end