function y = forward( NN, x )
    y = x;
    for j = 1:length( NN )
        y = NN{j}.forward( y );
    end
end

