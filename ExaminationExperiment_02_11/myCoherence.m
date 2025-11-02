function fig_handling = myCoherence(f, C, fig_title, fig_handling)
    % mybode(f, ~, C, fig_title)
    % mybode(f, ~, C, fig_title, fig_handling)
    % Plots ONLY the coherence(s) C vs frequency f.
    % Returns a struct with handles for re-use.
    %
    % Inputs:
    %   f  : frequency vector [Nx1] or [NxM] (one column per C-series)
    %   C  : coherence(s) [NxM]
    %   fig_title : title string
    %   fig_handling (optional) : struct with persistent handles
    %
    % Notes:
    %   - H and phase are intentionally ignored.
    %   - If f is a single column and C has M columns, f is replicated to match M.

    %==== Create or re-use figure/layout (single tile) ====%
    if nargin < 5 || ~isstruct(fig_handling) || ~isfield(fig_handling,'fig') || ~isvalid(fig_handling.fig)
        fig_handling = struct();
        fig_handling.fig = figure('Name', "Coherence: " + fig_title);
        fig_handling.t   = tiledlayout(fig_handling.fig, 1, 1, "TileSpacing", "tight");
        title(fig_handling.t, 'Coherence: ' + fig_title, 'FontSize', 24);
        fig_handling.Coh_tile = nexttile(fig_handling.t, 1);
    else
        figure(fig_handling.fig);
        if ~isfield(fig_handling,'Coh_tile') || isempty(fig_handling.Coh_tile) || ~isgraphics(fig_handling.Coh_tile)
            fig_handling.Coh_tile = nexttile(fig_handling.t, 1);
        end
    end

    %==== Validate inputs ====%
    if isempty(C)
        cla(fig_handling.Coh_tile);
        xlabel(fig_handling.Coh_tile, 'Frequency [Hz]','FontSize',24);
        ylabel(fig_handling.Coh_tile, 'Coherence [-]','FontSize',24);
        title(fig_handling.Coh_tile, 'Coherence','FontSize',24);
        grid(fig_handling.Coh_tile, 'on'); set(fig_handling.Coh_tile,'XScale','log'); ylim(fig_handling.Coh_tile,[0 1]);
        return;
    end

    % Ensure f has same column count as C
    [Nf,Mf] = size(f);
    [Nc,Mc] = size(C);
    if Nf ~= Nc
        error('Size mismatch: length(f) must equal size(C,1).');
    end
    if Mf == 1 && Mc > 1
        f = repmat(f, 1, Mc);
    elseif Mf ~= Mc
        error('Column mismatch: size(f,2) must be 1 or equal to size(C,2).');
    end

    %==== Plot coherences ====%
    ax = fig_handling.Coh_tile;
    hold(ax, 'on');
    % If reusing, clear only line objects we own
    if isfield(fig_handling,'C_plot') && all(isgraphics(fig_handling.C_plot))
        delete(fig_handling.C_plot(ishandle(fig_handling.C_plot)));
    end

    fig_handling.C_plot = gobjects(1, size(C,2));
    for i = 1:size(C,2)
        fig_handling.C_plot(i) = plot(ax, f(:,i), C(:,i));
    end

    set(ax, 'XScale', 'log');
    grid(ax, 'on');
    ylim(ax, [0 1]);
    xlabel(ax, 'Frequency [Hz]','FontSize',24);
    ylabel(ax, 'Coherence [-]','FontSize',24);
    %title(ax, 'Coherence','FontSize',24);

    % Optional: leave legend to caller; they can do:
    %   legend(fig_handling.C_plot, {"Coh_{ps}", "Coh_{s}"}, 'Interpreter','latex')
end
