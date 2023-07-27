%Plot a grid x*y of neuron potentials.
%Table columns: Step, Layer_ID, Id, V, I, I_Bias
function plot_voltage(log_file, x, y)
    % Read the log file
    data = readtable(log_file);

    % Get the unique steps
    steps = unique(data.Step);
    ids = unique(data.Id);

    % Number of neurons to plot
    num_neurons = x * y;

    if (num_neurons > length(ids))
        disp("Reduce the dimension of the subplot");
        return
    end

    % Create a subplot for each neuron ID
    sub_plot_pos = 1;
    for i = 1:num_neurons
        neuron_id = ids(i);
        layer_id = data(data.Id == neuron_id, :).Layer_ID(1);

        % Extract neuron data for the current neuron ID
        neuron_data = data(data.Id == neuron_id, :);


        % Create a subplot for membrane potential 
        subplot(x, y, sub_plot_pos);
        plot(steps, neuron_data.V);
        title(sprintf('Neuron %d, Layer %d', neuron_id, layer_id));
        xlabel('Step');
        ylabel('Potential (mV)');
        sub_plot_pos = sub_plot_pos + 1;

    
    end
end
