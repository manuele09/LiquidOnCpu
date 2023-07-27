function visualize_network_connectivity(file_path)
    % Load the data from the file
    data = load(file_path);

    % Extract data columns
    pre_id = data(:, 1);
    post_id = data(:, 2);
    pre_layer_id = data(:, 3);
    post_layer_id = data(:, 4);

    % Offset the node IDs to start from 1
    min_node_id = min(min(pre_id), min(post_id));
    pre_id = pre_id - min_node_id + 1;
    post_id = post_id - min_node_id + 1;

    % Create a directed graph object
    num_neurons = max([pre_id; post_id]);
    G = digraph(pre_id, post_id);

    % Create node names based on layer information
    node_names = cell(num_neurons, 1);
    for i = 1:num_neurons
        node_names{i} = sprintf('Layer %d, Neuron %d', post_layer_id(i), i);
    end

    % Compute the x-coordinates for each neuron based on layer information
    num_layers = max([pre_layer_id; post_layer_id]);
    layer_spacing = 100; % Adjust this value to control the spacing between layers
    x_coords = zeros(num_neurons, 1);
    for layer = 1:num_layers
        neurons_in_layer = find(post_layer_id == layer);
        num_neurons_in_layer = numel(neurons_in_layer);
        x_coords(neurons_in_layer) = (1:num_neurons_in_layer) * layer_spacing;
    end

    % Compute the y-coordinates for each neuron (all neurons on the same y-level)
    y_coords = ones(num_neurons, 1) * 100; % Adjust this value to control the y-level

    % Plot the graph with custom layout and arrows
    figure;
    h = plot(G, 'XData', x_coords, 'YData', y_coords, 'NodeLabel', node_names, 'ArrowSize', 8);

    % Customize the plot appearance (optional)
    title('Network Connectivity Visualization');
    xlabel('Layer');
    ylabel('Neuron');
    axis tight;
    set(gca, 'YTick', []);
    
    % Adjust the node and edge colors (optional)
    highlight(h, find(post_layer_id == 1), 'NodeColor', 'r');
    highlight(h, find(post_layer_id == 2), 'NodeColor', 'g');
    highlight(h, find(post_layer_id == 3), 'NodeColor', 'b');

    % Legend (optional, if you used different colors)
    legend('Layer 1', 'Layer 2', 'Layer 3');

    % Uncomment the line below to save the plot as an image
    % saveas(gcf, 'network_connectivity_plot.png');
end
