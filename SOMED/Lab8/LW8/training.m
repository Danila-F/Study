function e = training(NN, E, x)
    y = forward( NN, x );
    loss = E.forward( y );
    dE = E.backward( y );
    
    for i = length(NN):-1:1
        dE = NN{i}.backward(dE);
    end
    
    e = mean(loss);
end