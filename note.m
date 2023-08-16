function [Uopt, rho] = MSPHDEC(U, d2, i, rho, U_hat_unc, Nc, H, Uopt)
    for u = -1:1
        U(i) = u;
        d2_new = norm(U_hat_unc(i, :) - H(i, 1:i)*U(1:i)') + d2;
        if d2_new < rho
            if i < 3 * Nc
                [Uopt,rho] = MSPHDEC(U, d2_new, i+1, rho, U_hat_unc, Nc, H, Uopt);
            else
                Uopt = U;
                rho = d2_new;
            end
        end
    end
    end