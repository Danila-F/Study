classdef Dense < handle
    
    properties( Access = public )
        in_dim;
        out_dim;
        w;
        lr;
        x;
    end

%     properties( Constant )
%         N = 4;
%     end

%     methods ( Abstract, Access = public )
%         [ y ] = my_func( x );
%     end

    methods
        function self = Dense( varargin )
            if nargin > 0
                self.out_dim = varargin{ 1 };
                self.in_dim = varargin{ 2 };
                self.lr = varargin{ 3 }; %learning rate
                
                % fill
                self.w = ...
            end
        end
        
        function y = forward( self, x )
            self.x = x;
            
            % fill
            y = ...
        end
        
        function dx = backward( self, dy )
            dx = self.w' * dy;
            
            % fill
            dw = ...
            self.w = self.w - self.lr * dw;
        end

        function disp( self )
            fprintf( 'shape = ( %d, %d )\n', self.in_dim, self.out_dim );
        end      
    end

%     methods( Static )
%         function self = rand( varargin )
%             if nargin == 3
%                 out_dim = varargin{ 1 };
%                 in_dim = varargin{ 2 };
%                 lr = varargin{ 3 };
%                 self = Dense( randn( out_dim, in_dim ) / in_dim, lr );
%             else
%                 error( 'Enter 3 values!' );
%             end
%         end
%     end

    %% Override methods
%     methods
%         function y = my_func( self, x )
%             y = self.k * x;
%         end
%     end
end
