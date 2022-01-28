classdef E_logloss
    properties( Access = public )
        labels;
    end
    
    methods
        % конструктор класса
        function self = E_logloss( varargin )
            if nargin > 0
                % конвертирование в onehot-код
                % varargin{1} - первый аргумент переданный в функцию
                self.labels = varargin{1}==(0:9)';
            else
                error( 'Enter 1 value!' );
            end
        end
        
        function y = forward( self, x )
            % fill
            y = ...
        end
        
        function dx = backward( self, x )
            % с учетом того, что последний слой использует функцию
            % активации softmax
            % fill
            dx = ...
        end
    end
end