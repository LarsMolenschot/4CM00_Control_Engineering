function fig_handling = mybode(f, H, C, fig_title, fig_handling)
    % mybode(f, H, C, fig_title)
    % mybode(f, H, C, fig_title, fig_handling)
    % Creates or updates a tiled Bode figure.
    % Returns a struct with handles for re-use.

    %=== Create new figure if needed ===%
    if nargin < 5 || ~isstruct(fig_handling) || ~isvalid(fig_handling.fig)
        fig_handling.fig = figure('Name', "Bode: " + fig_title);
        fig_handling.t = tiledlayout(fig_handling.fig, 3, 1, "TileSpacing", "tight");
        title(fig_handling.t, 'Bode: ' + fig_title);

        % Create tiles
        fig_handling.H_tile   = nexttile(fig_handling.t, 1);
        fig_handling.P_tile   = nexttile(fig_handling.t, 2);

        if ~isempty(C) && size(C,2) > 0
            fig_handling.Coh_tile = nexttile(fig_handling.t, 3);
        else
            fig_handling.Coh_tile = [];
        end
    else
        % Reuse existing layout
        figure(fig_handling.fig);
        needsCoh = (~isfield(fig_handling,"Coh_tile") || ...
             isempty(fig_handling.Coh_tile) || ...
             ~isgraphics(fig_handling.Coh_tile));

        if needsCoh && ~isempty(C) && size(C,2) > 0
            fig_handling.Coh_tile = nexttile(fig_handling.t, 3);
        end
    end

    hold(fig_handling.H_tile, 'on');
    hold(fig_handling.P_tile, 'on');
    if isgraphics(fig_handling.Coh_tile)
        hold(fig_handling.Coh_tile, 'on');
    end
    %=== Prepare frequency matrix ===%
    if size(f, 2) == 1
        f = repmat(f, 1, size(H, 2));
    end
    % if(size_f(2) == 1) %copy the freq to use for all plots
    %     f_copy = f;
    %     f = zeros(size(H));
    %     for i = 1 : size_h(2)
    %         f(:,i) = f_copy;
    %     end
    % end

    %=== Magnitude ===%
    for i = 1:size(H, 2)
        plot(fig_handling.H_tile, f(:,i), 20*log10(abs(H(:,i))));
    end
    set(fig_handling.H_tile, 'XScale', 'log'); grid(fig_handling.H_tile, 'on');
    ylabel(fig_handling.H_tile, '|H| [dB]');
    title(fig_handling.H_tile, 'Magnitude');

    %=== Phase ===%
    for i = 1:size(H, 2)
        plot(fig_handling.P_tile, f(:,i), rad2deg(angle(H(:,i))));
    end
    set(fig_handling.P_tile, 'XScale', 'log'); grid(fig_handling.P_tile, 'on');
    ylabel(fig_handling.P_tile, 'Phase [deg]');
    title(fig_handling.P_tile, 'Phase');

    size_c = size(C);
    if(~size_c(2))
        xlabel('Frequency [Hz]');
        return;
    end
    %=== Coherence ===%
    if ~isempty(C)
        for i = 1:size(C, 2)
            plot(fig_handling.Coh_tile, f(:,ceil(i/2)), C(:,i));
        end
        set(fig_handling.Coh_tile, 'XScale', 'log');
        grid(fig_handling.Coh_tile, 'on');
        xlabel(fig_handling.Coh_tile, 'Frequency [Hz]');
        title(fig_handling.Coh_tile, 'Coherence');
    end
end
