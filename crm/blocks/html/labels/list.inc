<?php
/**
 * @copyright 2013 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
?>
<div>
	<h2><?php
			echo $this->translate(array('labels.label', 'labels.labels', 2));
			if (userIsAllowed('labels','update')) {
				echo sprintf('<a class="btn" href="%s"><span class="icon-plus"></span> %s</a>',
					BASE_URI.'/labels/update',
					$this->translate('labels.add')
				);
			}
		?>
	</h2>
	<p><?php echo $this->translate('text.labels_description'); ?></p>
	<ul>
	<?php
		$list = new LabelList();
		$list->find();
 		foreach ($list as $label) {
			if (userIsAllowed('labels','update')) {
				$editButton = "
				<a class=\"btn\"
					href=\"".BASE_URI."/labels/update?label_id={$label->getId()}\">
					<span class=\"icon-pencil\"></span>
					{$this->translate('labels.edit')}
				</a>
				";
			}
			$name = View::escape($label->getName());
			echo "<li>$editButton $name</li>";
		}
	?>
	</ul>
</div>
