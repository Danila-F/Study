clear;

x_in = 1:8;
x_out = zeros(1, 8);

Wkn_in = 1:4;
Wkn_out = zeros(1, 4);

N  = 8;     %data length
N2 = 1;     %pointer to the second X operand
IE = N/2;   %increment for Wkn indexes
I  = 0;     %indexes for input data
J  = 0;     %increment for I indexes
K  = 0;     %indexes for Wkn

while N2 < N
    K = 0;
    J = 0;
    while J < N2
        I = J;
        while I < N
            %%% butterfly function %%%
            x_out(I+1) = x_in(I+1);
            x_out(I + N2 + 1) = x_in(I + N2 + 1);
            
            Wkn_out(K+1) = Wkn_in(K+1);
            
            I = I + 2 * N2;
        end
        K = K + IE;
        J = J + 1;
    end
    x_out = zeros(1, 8);
    Wkn_out = zeros(1, 4);
    IE = IE / 2;
    N2 = 2 * N2;
end